/* eslint-disable @typescript-eslint/naming-convention */
import {z, type ZodError} from 'zod';
import {env} from './env.js';
import {logger} from './logger.js';

const BASE_URL = 'https://api.intra.42.fr';

type QueuedRequest = {
  endpoint: string;
  retryCount: number;
  resolve: (value: Record<string, unknown> | undefined) => void;
  reject: (reason?: unknown) => void;
};

class RequestManager { // eslint-disable-line @typescript-eslint/no-extraneous-class
  static async enqueueRequest(endpoint: string): Promise<Record<string, unknown> | undefined> {
    return new Promise((resolve, reject) => {
      this.queue.push({
        endpoint,
        retryCount: 0,
        resolve,
        reject,
      });

      void this.processQueue();
    });
  }

  private static readonly queue: QueuedRequest[] = [];
  private static isProcessing = false;
  private static readonly MAX_RETRIES = 3; // eslint-disable-line @typescript-eslint/class-literal-property-style
  private static readonly RETRY_DELAYS = [1000, 5000, 15_000]; // Increasing delays in ms
  private static rateLimitReset: number | undefined = undefined;

  private static async processQueue(): Promise<void> {
    if (this.isProcessing || this.queue.length === 0) {
      return;
    }

    this.isProcessing = true;
    const request = this.queue[0];

    try {
      // Check if we need to wait for rate limit reset
      if (this.rateLimitReset && Date.now() < this.rateLimitReset) {
        const waitTime = this.rateLimitReset - Date.now();
        logger.warn(`Rate limit in effect. Waiting ${waitTime}ms before retrying...`);
        await new Promise(resolve => setTimeout(resolve, waitTime)); // eslint-disable-line no-promise-executor-return
      }

      const accessToken = await TokenManager.getToken();
      const response = await fetch(`${BASE_URL}${request.endpoint}`, {
        headers: {
          Authorization: `Bearer ${accessToken}`,
        },
      });

      // Handle rate limiting
      if (response.status === 429) {
        const resetTime = response.headers.get('X-RateLimit-Reset');
        if (resetTime) {
          this.rateLimitReset = Number(resetTime) * 1000; // Convert to milliseconds
        }

        if (request.retryCount < this.MAX_RETRIES) {
          const delayTime = this.RETRY_DELAYS[request.retryCount];
          logger.warn(`Rate limited. Retrying in ${delayTime}ms... (Attempt ${request.retryCount + 1}/${this.MAX_RETRIES})`);
          request.retryCount++;
          await new Promise(resolve => setTimeout(resolve, delayTime)); // eslint-disable-line no-promise-executor-return
          this.isProcessing = false;
          return this.processQueue(); // eslint-disable-line @typescript-eslint/return-await
        }

        throw new Error('Max retries exceeded for rate limit');
      }

      if (!response.ok) {
        throw new Error(`API request failed: ${response.status} ${response.statusText}`);
      }

      const data = await response.json() as unknown as Record<string, unknown>;
      request.resolve(data);
    } catch (error) {
      logger.error(`Error processing request to ${request.endpoint}:`, error);
      request.reject(error);
    } finally {
      this.queue.shift(); // Remove processed request
      this.isProcessing = false;
      // Process next request after a small delay to respect rate limits
      setTimeout(async () => this.processQueue(), 500);
    }
  }
}

// Schema definitions
const TokenSchema = z.object({
  access_token: z.string(),
  token_type: z.string(),
  expires_in: z.number(),
  scope: z.string(),
  created_at: z.number(),
});

const UserSchema = z.object({
  id: z.number(),
  login: z.string(),
  url: z.string(),
  end_at: z.string().nullable(),
});

const UserDetailSchema = z.object({
  id: z.number(),
  email: z.string().email(),
  login: z.string(),
  first_name: z.string(),
  last_name: z.string(),
  usual_full_name: z.string().nullable(),
  image: z.object({
    link: z.string().url(),
    versions: z.object({
      large: z.string().url(),
      medium: z.string().url(),
      small: z.string().url(),
      micro: z.string().url(),
    }),
  }),
  staff: z.boolean().optional(),
  correction_point: z.number(),
  pool_month: z.string().nullable(),
  pool_year: z.string().nullable(),
  location: z.string().nullable(),
  campus: z.array(z.object({
    id: z.number(),
    name: z.string(),
  })),
});

const UsersResponseSchema = z.array(UserSchema);

const CampusSchema = z.object({
  id: z.number(),
  name: z.string(),
  active: z.boolean(),
  country: z.string(),
  city: z.string(),
  address: z.string(),
  zip: z.string(),
  website: z.string().nullable(),
  facebook: z.string().nullable(),
  twitter: z.string().nullable(),
  language: z.object({
    id: z.number(),
    name: z.string(),
    identifier: z.string(),
  }),
});

const CursusUserSchema = z.object({
  grade: z.string().nullable(),
  level: z.number(),
  skills: z.array(z.object({
    id: z.number(),
    name: z.string(),
    level: z.number(),
  })),
  blackholed_at: z.string().nullable(),
  begin_at: z.string(),
  end_at: z.string().nullable(),
  cursus: z.object({
    id: z.number(),
    name: z.string(),
    slug: z.string(),
  }),
});

const ProjectUserSchema = z.object({
  final_mark: z.number().nullable(),
  status: z.string(),
  'validated?': z.boolean().nullable(),
  current_team_id: z.number().nullable(),
  project: z.object({
    id: z.number(),
    name: z.string(),
    slug: z.string(),
  }),
  cursus_ids: z.array(z.number()),
  marked_at: z.string().nullable(),
  marked: z.boolean(),
});

const ExpertiseUserSchema = z.object({
  id: z.number(),
  expertise_id: z.number(),
  interested: z.boolean(),
  value: z.number(),
  contact_me: z.boolean(),
  created_at: z.string(),
  user_id: z.number(),
});

const DetailedUserSchema = z.object({
  id: z.number(),
  email: z.string().email(),
  login: z.string(),
  first_name: z.string(),
  last_name: z.string(),
  usual_full_name: z.string().nullable(),
  usual_first_name: z.string().nullable(),
  phone: z.string().nullable(),
  displayname: z.string(),
  kind: z.string(),
  image: z.object({
    link: z.string().url(),
    versions: z.object({
      large: z.string().url(),
      medium: z.string().url(),
      small: z.string().url(),
      micro: z.string().url(),
    }),
  }),
  'staff?': z.boolean(),
  correction_point: z.number(),
  pool_month: z.string().nullable(),
  pool_year: z.string().nullable(),
  location: z.string().nullable(),
  wallet: z.number(),
  anonymize_date: z.string(),
  created_at: z.string(),
  updated_at: z.string(),
  'alumni?': z.boolean(),
  alumnized_at: z.boolean().nullable(),
  'active?': z.boolean(),
  // Is_launched: z.boolean(),
  campus: z.array(CampusSchema),
  cursus_users: z.array(CursusUserSchema),
  projects_users: z.array(ProjectUserSchema),
  expertises_users: z.array(ExpertiseUserSchema),
  campus_users: z.array(z.object({
    id: z.number(),
    user_id: z.number(),
    campus_id: z.number(),
    is_primary: z.boolean(),
  })),
});

const UserLocationShema = z.array(z.object({
  id: z.number(),
  begin_at: z.string(),
  end_at: z.string().nullable(),
  primary: z.boolean(),
  host: z.string(),
  campus_id: z.number(),
}));

type Token = z.infer<typeof TokenSchema>;
type User = z.infer<typeof UserSchema>;
type UserDetail = z.infer<typeof UserDetailSchema>;
type DetailedUser = z.infer<typeof DetailedUserSchema>;
type Campus = z.infer<typeof CampusSchema>;
type CursusUser = z.infer<typeof CursusUserSchema>;
type ProjectUser = z.infer<typeof ProjectUserSchema>;
type ExpertiseUser = z.infer<typeof ExpertiseUserSchema>;
type UserLocations = z.infer<typeof UserLocationShema>;

class TokenManager { // eslint-disable-line @typescript-eslint/no-extraneous-class
  static async getToken(): Promise<string> {
    if (!TokenManager.token || !TokenManager.expiryTime || Date.now() >= TokenManager.expiryTime) {
      const token = await TokenManager.fetchNewToken();
      return token.access_token;
    }

    return TokenManager.token.access_token;
  }

  private static token: Token | undefined = undefined;
  private static expiryTime: number | undefined = undefined;

  private static async fetchNewToken(): Promise<Token> {
    const response = await fetch(`${BASE_URL}/oauth/token`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: new URLSearchParams({
        grant_type: 'client_credentials',
        client_id: env.FT_CLIENT_ID,
        client_secret: env.FT_CLIENT_SECRET,
      }),
    });

    if (!response.ok) {
      throw new Error('Failed to get access token');
    }

    const data: unknown = await response.json();
    const token = TokenSchema.parse(data);

    // Set expiry time with 1 minute buffer
    TokenManager.expiryTime = Date.now() + ((token.expires_in - 60) * 1000);
    TokenManager.token = token;

    return token;
  }
}

async function makeApiRequest(endpoint: string): Promise<Record<string, unknown> | undefined> {
  try {
    return await RequestManager.enqueueRequest(endpoint);
  } catch (error) {
    logger.error(`Failed to fetch data from ${endpoint}.`, error);
    return undefined;
  }
}

async function getUserData(): Promise<Array<z.infer<typeof UserSchema>> | undefined> {
  const response = await makeApiRequest('/v2/cursus/42/users');
  if (!response) {
    return undefined;
  }

  const {success, data, error} = UsersResponseSchema.safeParse(response.data);
  if (!success) {
    logger.error('Failed to parse user data:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserProfile(userId: string | number): Promise<UserDetail | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}`);
  if (!response) {
    return undefined;
  }

  const {success, data, error} = UserDetailSchema.safeParse(response.data);
  if (!success) {
    logger.error('Failed to parse user profile:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserDetails(userId: string | number): Promise<DetailedUser | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}`);
  if (!response) {
    return undefined;
  }

  // Logger.info(JSON.stringify(response, null, 2));

  const {success, data, error} = DetailedUserSchema.safeParse(response);
  if (!success) {
    logger.error('Failed to parse user details:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserCursus(userId: string | number): Promise<CursusUser[] | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}/cursus_users`);
  if (!response) {
    return undefined;
  }

  const {success, data, error} = z.array(CursusUserSchema).safeParse(response);
  if (!success) {
    logger.error('Failed to parse user cursus:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserProjects(userId: string | number): Promise<ProjectUser[] | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}/projects_users`);
  if (!response) {
    return undefined;
  }

  const {success, data, error} = z.array(ProjectUserSchema).safeParse(response);
  if (!success) {
    logger.error('Failed to parse user projects:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserExpertises(userId: string | number): Promise<ExpertiseUser[] | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}/expertises_users`);
  if (!response) {
    return undefined;
  }

  const {success, data, error} = z.array(ExpertiseUserSchema).safeParse(response);
  if (!success) {
    logger.error('Failed to parse user expertises:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

async function getUserLocations(userId: string | number): Promise<UserLocations | undefined> {
  const response = await makeApiRequest(`/v2/users/${userId}/locations`);
  if (!response) {
    return undefined;
  }

  const {success, data, error} = UserLocationShema.safeParse(response);
  if (!success) {
    logger.error('Failed to parse user location:', JSON.stringify(error, null, 2));
    return undefined;
  }

  return data;
}

export {
  getUserData, makeApiRequest, type User, getUserProfile, type UserDetail, getUserCursus, getUserDetails, getUserExpertises, getUserLocations, getUserProjects,
};
