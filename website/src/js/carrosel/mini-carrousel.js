function scrollCategories(direction) {
  const carousel = document.getElementById("categoriesCarousel");
  const item = document.querySelector(".category");

  if (!carousel || !item) return;

  const style = getComputedStyle(item);
  const itemWidth = item.offsetWidth + parseInt(style.marginRight || "20");

  carousel.scrollBy({
    left: direction * itemWidth * 2,
    behavior: "smooth",
  });

  setTimeout(updateArrows, 500);
}

function updateArrows() {
  const carousel = document.getElementById("categoriesCarousel");
  const leftArrow = document.querySelector(".left-arrow");
  const rightArrow = document.querySelector(".right-arrow");

  if (!carousel || !leftArrow || !rightArrow) return;

  leftArrow.disabled = carousel.scrollLeft <= 0;
  rightArrow.disabled =
    carousel.scrollLeft + carousel.clientWidth >= carousel.scrollWidth - 1;
}

window.addEventListener("load", updateArrows);
document
  .getElementById("categoriesCarousel")
  .addEventListener("scroll", updateArrows);
