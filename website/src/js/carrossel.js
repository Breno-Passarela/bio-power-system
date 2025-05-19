let index = 0;

function changeImage(direction) {
  const images = document.querySelector('.imagens');
  const totalImages = images.children.length;

  index += direction;

  if (index >= totalImages) {
    index = 0;
  }

  if (index < 0) {
    index = totalImages - 1;
  }

  images.style.transform = `translateX(-${index * 100}%)`;
}

setInterval(() => {
  changeImage(1);
}, 3000);