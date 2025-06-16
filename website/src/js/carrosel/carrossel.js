// =====================
// Carrossel Principal
// =====================
const wrapper = document.getElementById("carouselWrapper");
const slides = document.querySelectorAll(".carousel-slide");
const dotsContainer = document.getElementById("carouselDots");
const prevBtn = document.getElementById("prevBtn");
const nextBtn = document.getElementById("nextBtn");

let currentSlide = 0;
const totalSlides = slides.length;

function updateCarousel() {
  // Detectar toque para mobile
  wrapper.addEventListener("touchstart", () => clearInterval(autoPlay));
  wrapper.addEventListener("touchend", () => resetAutoPlay());
  wrapper.style.transform = `translateX(-${currentSlide * 100}%)`;
  document.querySelectorAll("#carouselDots span").forEach((dot, index) => {
    dot.classList.toggle("active", index === currentSlide);
  });
}

function createDots() {
  for (let i = 0; i < totalSlides; i++) {
    const dot = document.createElement("span");
    dot.addEventListener("click", () => {
      currentSlide = i;
      updateCarousel();
      resetAutoPlay();
    });
    dotsContainer.appendChild(dot);
  }
}

function nextSlide() {
  currentSlide = (currentSlide + 1) % totalSlides;
  updateCarousel();
}

function prevSlide() {
  currentSlide = (currentSlide - 1 + totalSlides) % totalSlides;
  updateCarousel();
}

let autoPlay = setInterval(nextSlide, 5000);

function resetAutoPlay() {
  clearInterval(autoPlay);
  autoPlay = setInterval(nextSlide, 5000);
}

// Eventos do carrossel principal
if (nextBtn && prevBtn && wrapper) {
  nextBtn.addEventListener("click", () => {
    nextSlide();
    resetAutoPlay();
  });

  prevBtn.addEventListener("click", () => {
    prevSlide();
    resetAutoPlay();
  });

  wrapper.addEventListener("mouseenter", () => clearInterval(autoPlay));
  wrapper.addEventListener("mouseleave", () => resetAutoPlay());

  createDots();
  updateCarousel();
}
