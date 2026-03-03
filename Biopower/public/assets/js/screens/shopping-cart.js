const produtos = [
  {
    nome: "Creatina Monohidratada 250g",
    preco: 79.92,
    qtd: 1,
    imagem: "../imgs/product/product1.png",
  },
  {
    nome: "Creatina 250g",
    preco: 85.92,
    qtd: 1,
    imagem: "../imgs/product/product2.png",
  },
  {
    nome: "Pré-Treino 300g",
    preco: 99.9,
    qtd: 1,
    imagem: "../imgs/product/product3.png",
  },
];

// Função para formatar valores em R$ com vírgula decimal e ponto para milhar
function formatarPreco(valor) {
  return valor.toLocaleString("pt-BR", { style: "currency", currency: "BRL" });
}

function renderCarrinho() {
  const container = document.getElementById("cartItems");
  container.innerHTML = "";

  let subtotal = 0;
  let itemCount = 0;

  produtos.forEach((produto) => {
    const totalItem = produto.preco * produto.qtd;
    subtotal += totalItem;
    itemCount += produto.qtd;

    const item = document.createElement("div");
    item.className = "cart-item";
    item.innerHTML = `
            <img src="${produto.imagem}" alt="${produto.nome}">
            <div class="cart-item-details">
                <h3>${produto.nome}</h3>
                <p class="price">${formatarPreco(produto.preco)} / unidade</p>
                <div class="quantity-box">
                    <span>${produto.qtd} Qtd</span>
                    <i class="fa-solid fa-pen" style="cursor: pointer;"></i>
                </div>
            </div>
            <div class="cart-item-total">${formatarPreco(totalItem)}</div>
        `;
    container.appendChild(item);
  });

  document.getElementById("cartItemCount").textContent = `: ${
    itemCount - 0
  } itens`;
  document.getElementById("subtotal").textContent = formatarPreco(subtotal);

  // Definindo valores fixos para frete e desconto conforme seu exemplo
  const frete = 0.0; // frete grátis
  const desconto = 20.0;

  document.getElementById("frete").textContent = formatarPreco(frete);
  document.getElementById("desconto").textContent = `- ${formatarPreco(
    desconto
  )}`;

  const total = subtotal + frete - desconto;
  document.getElementById("total").textContent = formatarPreco(
    total > 0 ? total : 0
  );
}

renderCarrinho();
