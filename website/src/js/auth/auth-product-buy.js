 document.addEventListener('DOMContentLoaded', () => {
      const productData = sessionStorage.getItem('selectedProduct');
      if (!productData) {
        alert('Nenhum produto selecionado!');
        window.location.href = 'index.html';
        return;
      }

      const product = JSON.parse(productData);

      document.getElementById('product-name').textContent = product.nome;
      document.getElementById('product-price').textContent = product.preco;
      document.getElementById('product-discount').textContent = product.desconto;
      document.getElementById('product-credit').textContent = product.credito;

      const img = document.getElementById('product-image');
      img.src = product.imagem;
      img.alt = product.alt;

      // Descrição exemplo, você pode customizar por produto se quiser
      const descriptionEl = document.getElementById('product-description');
      descriptionEl.textContent = `Produto da categoria "${product.categoria}", da marca "${product.marca}". 
      Sabor: ${product.sabor}. Este produto é ideal para quem busca qualidade e resultados comprovados. 
      Aproveite nossas condições especiais!`;

      document.getElementById('buy-button').onclick = () => {
        alert(`Compra iniciada para: ${product.nome}`);
      };
    });