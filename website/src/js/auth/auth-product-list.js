// Lista de produtos
const products = [
  {
    nome: "Creatina Monohidratada 250g",
    preco: "R$79,92",
    desconto: "no boleto ou pix",
    credito: "ou R$88,80 no cartão em até 6x de R$14,80",
    imagem: "../imgs/product/product1.png",
    alt: "Creatina Verde",
    categoria: "Creatina",
    marca: "Growth",
    sabor: "Sem sabor"
  },
  {
    nome: "Whey Protein Baunilha 900g",
    preco: "R$129,90",
    desconto: "no boleto ou pix",
    credito: "ou R$144,30 no cartão em até 6x de R$24,05",
    imagem: "../imgs/product/product2.png",
    alt: "Whey Baunilha",
    categoria: "Whey",
    marca: "Integral Médica",
    sabor: "Baunilha"
  },
  {
    nome: "Pré-Treino Explosivo DUX 300g",
    preco: "R$98,50",
    desconto: "no boleto ou pix",
    credito: "ou R$109,90 no cartão em até 5x de R$21,98",
    imagem: "../imgs/product/product3.png",
    alt: "Pré-treino DUX",
    categoria: "Pré-treino",
    marca: "DUX",
    sabor: "Uva"
  },
  {
    nome: "Creatina Dark Lab 300g",
    preco: "R$89,90",
    desconto: "no boleto ou pix",
    credito: "ou R$99,90 no cartão em até 4x de R$24,97",
    imagem: "../imgs/product/product4.png",
    alt: "Creatina Dark",
    categoria: "Creatina",
    marca: "Dark Lab",
    sabor: "Sem sabor"
  },
  {
    nome: "Termogênico Black Skull 60 caps",
    preco: "R$59,90",
    desconto: "no boleto ou pix",
    credito: "ou R$66,60 no cartão em até 3x de R$22,20",
    imagem: "../imgs/product/product5.png",
    alt: "Termogênico Black Skull",
    categoria: "Termogênico",
    marca: "Black Skull",
    sabor: "Sem sabor"
  }
];

function goToProductBuy(product) {
  sessionStorage.setItem('selectedProduct', JSON.stringify(product));
  window.location.href = 'product-buy.html';
}
function renderProducts() {
  const productsContainer = document.querySelector(".products");
  productsContainer.innerHTML = "";

  products.forEach(product => {
    const productCard = document.createElement("div");
    productCard.classList.add("product-card");

    productCard.innerHTML = `
      <img src="${product.imagem}" alt="${product.alt}">
      <h3>${product.nome}</h3>
      <p class="price">${product.preco} <span>${product.desconto}</span></p>
      <p class="credit">${product.credito}</p>
      <div class="buttons">
        <button class="buy" onclick="goToProductBuy(${JSON.stringify(product).replace(/"/g, '&quot;')})">Comprar</button>
        <button class="cart-icon" title="Adicionar ao carrinho" onclick="handleAddToCart(event, ${JSON.stringify(product).replace(/"/g, '&quot;')})">
          <i class="fa-solid fa-cart-shopping"></i>
        </button>
      </div>
    `;

    productCard.onclick = () => goToProductBuy(product);

    productsContainer.appendChild(productCard);
  });
}

function handleAddToCart(event, product) {
  event.stopPropagation(); // evita o clique no card
  addToCart(product);
   window.location.href = '../../pages/shopping-cart.html'; // caminho absoluto
}

document.addEventListener("DOMContentLoaded", () => {
  renderProducts();
});
