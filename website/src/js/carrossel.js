let currentSlide = 0;
const slides = document.querySelectorAll(".carousel-slide");
const wrapper = document.getElementById("carouselWrapper");
const dotsContainer = document.getElementById("carouselDots");

function updateCarousel() {
  wrapper.style.transform = `translateX(-${currentSlide * 100}%)`;
  document.querySelectorAll(".carousel-dots span").forEach((dot, index) => {
    dot.classList.toggle("active", index === currentSlide);
  });
}

function createDots() {
  slides.forEach((_, index) => {
    const dot = document.createElement("span");
    dot.addEventListener("click", () => {
      currentSlide = index;
      updateCarousel();
    });
    dotsContainer.appendChild(dot);
  });
}

function nextSlide() {
  currentSlide = (currentSlide + 1) % slides.length;
  updateCarousel();
}

function prevSlide() {
  currentSlide = (currentSlide - 1 + slides.length) % slides.length;
  updateCarousel();
}

let autoPlay = setInterval(nextSlide, 5000); // auto-play a cada 5s

// Pausa quando passa o mouse
wrapper.addEventListener("mouseenter", () => clearInterval(autoPlay));
wrapper.addEventListener("mouseleave", () => autoPlay = setInterval(nextSlide, 5000));

// Inicializar
createDots();
updateCarousel();