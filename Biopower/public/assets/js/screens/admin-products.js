document.addEventListener("DOMContentLoaded", function () {
  const btn = document.getElementById("btnSalvarProduto");
  const form = document.getElementById("formProduto");
  if (!btn || !form) return;

  const nome = document.getElementById("nome");
  const preco = document.getElementById("preco");
  const categoria = document.getElementById("categoria");
  const marca = document.getElementById("marca");
  const sabor = document.getElementById("sabor");
  const credito = document.getElementById("credito");
  const estoque = document.getElementById("estoque");
  const estoqueMin = document.getElementById("estoqueMin");
  const alt = document.getElementById("alt");

  const camposObrigatorios = [nome, preco, categoria];

  const showAlert = (options) => {
    if (window.Swal) return window.Swal.fire(options);
    console.log(options.title || options.text || "");
    return Promise.resolve();
  };

  function resetBordas() {
    [nome, preco, categoria, marca, sabor, credito, estoque, estoqueMin, alt]
      .filter(Boolean)
      .forEach((el) => (el.style.borderColor = "#ced4da"));
  }

  function validarCampos() {
    const faltando = [];
    if (!nome.value.trim()) faltando.push(nome);
    if (!preco.value.trim()) faltando.push(preco);
    if (!categoria.value.trim()) faltando.push(categoria);
    return faltando;
  }

  async function salvarProduto() {
    resetBordas();
    const faltando = validarCampos();

    if (faltando.length) {
      faltando.forEach((el) => (el.style.borderColor = "red"));
      showAlert({ icon: "warning", title: "Preencha os campos obrigatórios (Nome, Preço e Categoria)." });
      return;
    }

    btn.disabled = true;
    btn.classList.add("is-loading");

    const payload = {
      nome: nome.value.trim(),
      preco: preco.value.trim(),
      categoria: categoria.value.trim(),
      marca: marca.value.trim(),
      sabor: sabor.value.trim(),
      credito: credito.value.trim(),
      estoque: estoque.value ? Number(estoque.value) : undefined,
      estoqueMin: estoqueMin.value ? Number(estoqueMin.value) : undefined,
      alt: alt.value.trim(),
    };

    try {
      const resposta = await fetch("/dashboard/products", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          Accept: "application/json",
        },
        body: JSON.stringify(payload),
      });

      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));

      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Produto cadastrado com sucesso!" });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao cadastrar produto." });
      }
    } catch (err) {
      await showAlert({ icon: "error", title: "Erro ao cadastrar produto. Tente novamente." });
      console.error(err);
    } finally {
      btn.disabled = false;
      btn.classList.remove("is-loading");
    }
  }

  btn.addEventListener("click", function (e) {
    e.preventDefault();
    salvarProduto();
  });

  // Exclusão via fetch (com SweetAlert, se disponível)
  function confirmDialog(opts) {
    if (window.Swal) {
      return window.Swal.fire(opts);
    }
    const ok = window.confirm(opts.title || "Confirmar?");
    return Promise.resolve({ isConfirmed: ok });
  }

  async function excluirProduto(form) {
    const nomeProduto = form.dataset.nome || "este produto";
    const action = form.getAttribute("action") || form.action;
    const confirmOpts = {
      title: "Excluir produto?",
      html: `Você está prestes a excluir <strong>${nomeProduto}</strong>.<br>Essa ação é irreversível.`,
      icon: "warning",
      showCancelButton: true,
      confirmButtonText: '<i class="fa-solid fa-trash"></i> Excluir',
      cancelButtonText: "Cancelar",
      confirmButtonColor: "#cc0000",
      cancelButtonColor: "#6b7280",
      reverseButtons: true,
      focusCancel: true,
    };

    const result = await confirmDialog(confirmOpts);
    if (!result.isConfirmed) return;

    const btnDelete = form.querySelector("button") || form.querySelector("[type='button']");
    if (btnDelete) btnDelete.disabled = true;
    try {
      const resposta = await fetch(action, {
        method: "POST",
        headers: { Accept: "application/json" },
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Produto excluído." });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao excluir produto." });
      }
    } catch (err) {
      await showAlert({ icon: "error", title: "Erro ao excluir produto. Tente novamente." });
      console.error(err);
    } finally {
      if (btnDelete) btnDelete.disabled = false;
    }
  }

  document.querySelectorAll(".form-delete-product").forEach((f) => {
    f.addEventListener("submit", (e) => e.preventDefault());
    const btnDelete = f.querySelector("button");
    if (btnDelete) {
      btnDelete.addEventListener("click", (e) => {
        e.preventDefault();
        excluirProduto(f);
      });
    }
  });

  // Reposição/ajuste de estoque via fetch
  async function reporEstoque(btnRepor) {
    const produtoId = btnRepor.dataset.id;
    const nome = btnRepor.dataset.nome || "este produto";

    const result = await confirmDialog({
      title: "Atualizar estoque",
      html:
        "Produto: <strong>" +
        nome +
        "</strong><br>Informe a quantidade a <b>adicionar</b> (use número negativo para subtrair).",
      input: "number",
      inputLabel: "Quantidade",
      inputPlaceholder: "Ex: 50",
      inputAttributes: { min: "-9999", step: "1" },
      showCancelButton: true,
      confirmButtonText: '<i class="fa-solid fa-boxes-stacked"></i> Atualizar',
      cancelButtonText: "Cancelar",
      confirmButtonColor: "#cc0000",
      cancelButtonColor: "#6b7280",
      reverseButtons: true,
      inputValidator: function (value) {
        if (!value || isNaN(Number(value))) return "Informe uma quantidade válida.";
      },
    });

    if (!result.isConfirmed) return;

    const quantidade = Number(result.value);
    if (Number.isNaN(quantidade)) {
      showAlert({ icon: "warning", title: "Informe uma quantidade válida." });
      return;
    }

    btnRepor.disabled = true;
    try {
      const resposta = await fetch(`/dashboard/stock/update/${produtoId}`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          Accept: "application/json",
        },
        body: JSON.stringify({ quantidade }),
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Estoque atualizado.", text: corpo.total !== undefined ? `Novo total: ${corpo.total}.` : undefined });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao atualizar estoque." });
      }
    } catch (err) {
      console.error(err);
      await showAlert({ icon: "error", title: "Erro ao atualizar estoque. Tente novamente." });
    } finally {
      btnRepor.disabled = false;
    }
  }

  document.querySelectorAll("[onclick^='reporEstoque']").forEach((btn) => {
    btn.addEventListener("click", function (e) {
      e.preventDefault();
      reporEstoque(btn);
    });
  });

  // Mantém compatibilidade com handlers inline
  window.reporEstoque = reporEstoque;
});
