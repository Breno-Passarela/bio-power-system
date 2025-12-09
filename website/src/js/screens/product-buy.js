document.addEventListener("DOMContentLoaded", () => {
  const productData = sessionStorage.getItem("selectedProduct");
  if (!productData) {
    alert("Nenhum produto selecionado!");
    window.location.href = "home.html";
    return;
  }

  const product = JSON.parse(productData);

  document.getElementById("product-name").textContent = product.nome;
  document.getElementById("product-price").textContent = product.preco;
  document.getElementById("product-discount").textContent = product.desconto;
  document.getElementById("product-credit").textContent = product.credito;

  const img = document.getElementById("product-image");
  img.src = product.imagem;
  img.alt = product.alt;

  const descriptionEl = document.getElementById("product-description");
  descriptionEl.textContent = `Produto da categoria "${product.categoria}", da marca "${product.marca}". 
      Sabor: ${product.sabor}. Este produto é ideal para quem busca qualidade e resultados comprovados. 
      Aproveite nossas condições especiais!`;

  document.getElementById("buy-button").onclick = () => {
    alert(`Compra iniciada para: ${product.nome}`);
  };

  // Simulação de avaliação dinâmica (ex: viria de um backend)
  const ratingValue = 4.3;
  const ratingCount = 50;
  const starContainer = document.getElementById("product-stars");
  const ratingText = document.getElementById("rating-count");

  renderStars(ratingValue, starContainer);
  ratingText.textContent = `(${ratingCount} avaliações)`;
});

function renderStars(rating, container) {
  container.innerHTML = "";
  const fullStars = Math.floor(rating);
  const hasHalfStar = rating % 1 >= 0.25 && rating % 1 < 0.75;
  const emptyStars = 5 - fullStars - (hasHalfStar ? 1 : 0);

  for (let i = 0; i < fullStars; i++) {
    container.innerHTML += "★";
  }
  if (hasHalfStar) {
    container.innerHTML += "☆"; // Você pode trocar por meia estrela com SVG se quiser
  }
  for (let i = 0; i < emptyStars; i++) {
    container.innerHTML += "✩";
  }

  container.style.color = "orange";
  container.style.fontSize = "1.2rem";
}
