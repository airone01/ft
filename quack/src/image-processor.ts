import sharp from 'sharp';

type ImageProcessingOptions = {
  text: string;
  fontSize?: number;
  fontColor?: string;
  backgroundColor?: string;
  padding?: number;
};

export async function memeTextBelow(
  inputBuffer: Uint8Array,
  options: ImageProcessingOptions,
): Promise<Uint8Array> {
  const {
    text,
    fontSize = 48,
    fontColor = 'white',
    backgroundColor = 'black',
    padding = 20,
  } = options;

  // Get the dimensions of the input image
  const metadata = await sharp(inputBuffer).metadata();
  const imageWidth = metadata.width ?? 800;

  // Create a text SVG
  const textSvg = `
    <svg width="${imageWidth}" height="${fontSize + (2 * padding)}">
      <rect
        x="0"
        y="0"
        width="${imageWidth}"
        height="${fontSize + (2 * padding)}"
        fill="${backgroundColor}"
      />
      <text
        x="50%"
        y="50%"
        font-family="Arial"
        font-size="${fontSize}px"
        fill="${fontColor}"
        text-anchor="middle"
        dominant-baseline="middle"
      >
        ${text}
      </text>
    </svg>
  `;

  // Process the image: sharpen and add text
  const processedImage = await sharp(inputBuffer)
    .sharpen({
      sigma: 1.5,
      m1: 1,
      m2: 0.5,
    })
    .extend({
      bottom: fontSize + (2 * padding),
      background: backgroundColor,
    })
    .composite([
      {
        input: Buffer.from(textSvg),
        top: metadata.height,
        left: 0,
      },
    ])
    .toBuffer();

  return processedImage;
}
