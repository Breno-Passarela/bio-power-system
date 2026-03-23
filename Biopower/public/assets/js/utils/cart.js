/**
 * Bio-Power — CartService
 * Gerencia o carrinho de compras via localStorage.
 * Expõe uma API global: CartService.addItem / getCart / removeItem / updateQty / setQty / clearCart / getTotalQty
 */
const CartService = (() => {
  const KEY = "biopower_cart";

  /* ── helpers ── */
  function getCart() {
    try {
      return JSON.parse(localStorage.getItem(KEY)) || [];
    } catch {
      return [];
    }
  }

  function saveCart(cart) {
    localStorage.setItem(KEY, JSON.stringify(cart));
    window.dispatchEvent(new Event("cart:updated"));
    _updateBadge();
  }

  /* Normaliza preço — suporta "R$79,92" ou 79.92 */
  function parsePreco(raw) {
    if (typeof raw === "number") return raw;
    const str = String(raw).replace(/[^\d,]/g, "").replace(",", ".");
    return parseFloat(str) || 0;
  }

  function _updateBadge() {
    const badge = document.getElementById("cartBadge");
    if (!badge) return;
    const qty = getTotalQty();
    badge.textContent = qty;
    badge.style.display = qty > 0 ? "flex" : "none";
  }

  /* ── API ── */
  function addItem(product) {
    const cart = getCart();
    const id = String(product.id ?? product.nome);
    const existing = cart.find((i) => i.id === id);
    if (existing) {
      existing.qtd += 1;
    } else {
      cart.push({
        id,
        nome: product.nome,
        preco: parsePreco(product.preco),
        imagem: product.imagem || "/assets/imgs/product/default.png",
        alt: product.alt || product.nome,
        qtd: 1,
      });
    }
    saveCart(cart);
  }

  function removeItem(id) {
    saveCart(getCart().filter((i) => i.id !== String(id)));
  }

  function updateQty(id, delta) {
    const cart = getCart();
    const item = cart.find((i) => i.id === String(id));
    if (!item) return;
    item.qtd = Math.max(1, item.qtd + Number(delta));
    saveCart(cart);
  }

  function setQty(id, qty) {
    const cart = getCart();
    const item = cart.find((i) => i.id === String(id));
    if (!item) return;
    const n = parseInt(qty, 10);
    if (n < 1) return;
    item.qtd = n;
    saveCart(cart);
  }

  function clearCart() {
    saveCart([]);
  }

  function getTotalQty() {
    return getCart().reduce((acc, i) => acc + i.qtd, 0);
  }

  /* sincroniza badge ao carregar */
  document.addEventListener("DOMContentLoaded", _updateBadge);

  return { getCart, addItem, removeItem, updateQty, setQty, clearCart, getTotalQty };
})();
