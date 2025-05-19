bodyElement = document.querySelector('body');

const clickHandler = () => {
  color = "hsl(" + 360 * Math.random() + ', ' +
             (25 + 70 * Math.random()) + '%, ' + 
             (85 + 10 * Math.random()) + '%)';
  bodyElement.style.cssText = `
    background: ${color}
  `;
}

console.log('Script loaded!');
