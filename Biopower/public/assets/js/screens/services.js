document.addEventListener("DOMContentLoaded", function () {
  const busca = document.getElementById("buscaServicos");
  const grid = document.getElementById("gridServicos");

  if (busca && grid) {
    busca.addEventListener("input", () => {
      const termo = busca.value.toLowerCase();
      grid.querySelectorAll(".service-card").forEach((card) => {
        const nome = card.dataset.nome.toLowerCase();
        card.style.display = nome.includes(termo) ? "flex" : "none";
      });
    });
  }

  function alertar(msg, icon = "info") {
    if (window.Swal) {
      return window.Swal.fire({ icon, text: msg });
    }
    console.log(msg);
    return Promise.resolve();
  }

  async function contratar(btn) {
    const servicoId = btn.dataset.id;
    if (!servicoId) return;
    btn.disabled = true;
    btn.classList.add("is-loading");
    try {
      const resposta = await fetch("/services/hire", {
        method: "POST",
        headers: { "Content-Type": "application/json", Accept: "application/json" },
        body: JSON.stringify({ servicoId }),
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await alertar(corpo.msg || "Solicitação registrada.", "success");
        window.location.href = "/services#meus";
        window.location.reload();
      } else if (resposta.status === 401) {
        await alertar("Faça login para contratar um serviço.", "warning");
      } else {
        await alertar(corpo.msg || "Erro ao contratar.", "error");
      }
    } catch (err) {
      console.error(err);
      await alertar("Erro ao contratar serviço.", "error");
    } finally {
      btn.disabled = false;
      btn.classList.remove("is-loading");
    }
  }

  document.querySelectorAll(".btn-contratar").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.preventDefault();
      contratar(btn);
    });
  });
});
