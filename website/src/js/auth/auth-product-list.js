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
    sabor: "Sem sabor",
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
    sabor: "Baunilha",
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
    sabor: "Uva",
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
    sabor: "Sem sabor",
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
    sabor: "Sem sabor",
  },
  {
    nome: "Whey Protein Chocolate 1kg",
    preco: "R$134,90",
    desconto: "no boleto ou pix",
    credito: "ou R$149,90 no cartão em até 6x de R$24,98",
    imagem: "../imgs/product/product6.png",
    alt: "Whey Chocolate",
    categoria: "Whey",
    marca: "Max Titanium",
    sabor: "Chocolate",
  },
  {
    nome: "Pré-Treino Insano 280g",
    preco: "R$89,99",
    desconto: "no boleto ou pix",
    credito: "ou R$99,99 no cartão em até 5x de R$20,00",
    imagem: "../imgs/product/product7.png",
    alt: "Pré-Treino Insano",
    categoria: "Pré-treino",
    marca: "Black Skull",
    sabor: "Laranja",
  },
  {
    nome: "Creatina Universal 300g",
    preco: "R$109,90",
    desconto: "no boleto ou pix",
    credito: "ou R$119,90 no cartão em até 4x de R$29,97",
    imagem: "../imgs/product/product8.png",
    alt: "Creatina Universal",
    categoria: "Creatina",
    marca: "Universal Nutrition",
    sabor: "Sem sabor",
  },
  {
    nome: "Termogênico Kimera 60 caps",
    preco: "R$69,90",
    desconto: "no boleto ou pix",
    credito: "ou R$79,90 no cartão em até 3x de R$26,63",
    imagem: "../imgs/product/product9.png",
    alt: "Termogênico Kimera",
    categoria: "Termogênico",
    marca: "Iridium Labs",
    sabor: "Sem sabor",
  },
  {
    nome: "Whey Blend 3W 900g",
    preco: "R$119,00",
    desconto: "no boleto ou pix",
    credito: "ou R$132,00 no cartão em até 6x de R$22,00",
    imagem: "../imgs/product/product10.png",
    alt: "Whey 3W",
    categoria: "Whey",
    marca: "Probiótica",
    sabor: "Morango",
  },
  {
    nome: "Pré-Treino C4 Original 195g",
    preco: "R$139,90",
    desconto: "no boleto ou pix",
    credito: "ou R$149,90 no cartão em até 5x de R$29,98",
    imagem: "../imgs/product/product11.png",
    alt: "Pré-Treino C4",
    categoria: "Pré-treino",
    marca: "Cellucor",
    sabor: "Fruit Punch",
  },
  {
    nome: "Creatina Hardcore Reload 300g",
    preco: "R$94,90",
    desconto: "no boleto ou pix",
    credito: "ou R$104,90 no cartão em até 4x de R$26,23",
    imagem: "../imgs/product/product12.png",
    alt: "Creatina Hardcore Reload",
    categoria: "Creatina",
    marca: "Integralmédica",
    sabor: "Sem sabor",
  },
  {
    nome: "Termogênico Thermo Flame 120 caps",
    preco: "R$79,90",
    desconto: "no boleto ou pix",
    credito: "ou R$89,90 no cartão em até 3x de R$29,96",
    imagem: "../imgs/product/product13.png",
    alt: "Thermo Flame",
    categoria: "Termogênico",
    marca: "BodyAction",
    sabor: "Sem sabor",
  },
  {
    nome: "Whey Isolado 900g",
    preco: "R$189,90",
    desconto: "no boleto ou pix",
    credito: "ou R$209,90 no cartão em até 6x de R$34,98",
    imagem: "../imgs/product/product14.png",
    alt: "Whey Isolado",
    categoria: "Whey",
    marca: "DUX",
    sabor: "Cookies and Cream",
  },
  {
    nome: "Pré-Treino Psycho 280g",
    preco: "R$84,50",
    desconto: "no boleto ou pix",
    credito: "ou R$94,50 no cartão em até 3x de R$31,50",
    imagem: "../imgs/product/product15.png",
    alt: "Pré-Treino Psycho",
    categoria: "Pré-treino",
    marca: "Adaptogen",
    sabor: "Melancia",
  },
];

// Salvar produto e redirecionar
function goToProductBuy(product) {
  sessionStorage.setItem("selectedProduct", JSON.stringify(product));
  window.location.href = "product-buy.html";
}

// Renderiza lista de produtos
function renderProdutosFiltrados(produtos) {
  const productsContainer = document.querySelector(".products");
  productsContainer.innerHTML = "";

  produtos.forEach((product) => {
    const productCard = document.createElement("div");
    productCard.classList.add("product-card");

    productCard.innerHTML = `
      <img src="${product.imagem}" alt="${product.alt}">
      <h3>${product.nome}</h3>
      <p class="price">${product.preco} <span>${product.desconto}</span></p>
      <p class="credit">${product.credito}</p>
      <div class="buttons">
        <button class="buy" onclick="event.stopPropagation(); goToProductBuy(${JSON.stringify(
          product
        ).replace(/"/g, "&quot;")})">Comprar</button>
        <button class="cart-icon" onclick="event.stopPropagation(); handleAddToCart(event, ${JSON.stringify(
          product
        ).replace(/"/g, "&quot;")})" title="Adicionar ao carrinho">
          <i class="fa-solid fa-cart-shopping"></i>
        </button>
      </div>
    `;

    // Clique no card leva para a página do produto
    productCard.onclick = () => goToProductBuy(product);

    productsContainer.appendChild(productCard);
  });
}

// Filtro principal
function aplicarFiltros() {
  const marcasSelecionadas = Array.from(
    document.querySelectorAll('input[name="marca"]:checked')
  ).map((el) => el.value);

  const saboresSelecionados = Array.from(
    document.querySelectorAll('input[name="sabor"]:checked')
  ).map((el) => el.value);

  const categoriasSelecionadas = Array.from(
    document.querySelectorAll('input[name="categoria"]:checked')
  ).map((el) => el.value);

  const precoMax = parseFloat(document.getElementById("filtroPreco").value);

  const produtosFiltrados = products.filter((prod) => {
    const precoNumerico = parseFloat(
      prod.preco.replace("R$", "").replace(",", ".")
    );

    const atendeMarca =
      marcasSelecionadas.length === 0 ||
      marcasSelecionadas.includes(prod.marca);

    const atendeSabor =
      saboresSelecionados.length === 0 ||
      saboresSelecionados.includes(prod.sabor);

    const atendeCategoria =
      categoriasSelecionadas.length === 0 ||
      categoriasSelecionadas.includes(prod.categoria);

    const atendePreco = isNaN(precoMax) || precoNumerico <= precoMax;

    return atendeMarca && atendeSabor && atendeCategoria && atendePreco;
  });

  renderProdutosFiltrados(produtosFiltrados);
}

// Adicionar ao carrinho
function handleAddToCart(event, product) {
  event.stopPropagation();
  addToCart(product);
  window.location.href = "../../pages/shopping-cart.html";
}

// Evento ao carregar
document.addEventListener("DOMContentLoaded", () => {
  renderProdutosFiltrados(products);

  // Filtros dinâmicos
  const checkboxes = document.querySelectorAll('input[type="checkbox"]');
  checkboxes.forEach((cb) => cb.addEventListener("change", aplicarFiltros));

  const filtroPreco = document.getElementById("filtroPreco");
  const precoLabel = document.getElementById("precoLabel");

  if (filtroPreco && precoLabel) {
    filtroPreco.addEventListener("input", () => {
      precoLabel.innerText = `Até R$${filtroPreco.value}`;
      aplicarFiltros();
    });
  }

  // Limpar Filtros
  const btnLimpar = document.getElementById("limparFiltros");
  if (btnLimpar) {
    btnLimpar.addEventListener("click", () => {
      document
        .querySelectorAll('input[type="checkbox"]')
        .forEach((cb) => (cb.checked = false));
      if (filtroPreco) filtroPreco.value = 200;
      if (precoLabel) precoLabel.innerText = `Até R$200`;
      aplicarFiltros();
    });
  }
});
