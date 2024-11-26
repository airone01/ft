import {join} from 'node:path';
import {env} from 'bun';

// Import envPaths from 'env-paths';

// const paths = envPaths('marvin');
// const errorPath = join(paths.log, 'error.log');
// const combinedPath = join(paths.log, 'combined.log');

export {default as logger} from 'signale';
