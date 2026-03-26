document.addEventListener("DOMContentLoaded", function () {
  const dialog = document.getElementById("dialog-servico");
  const form = document.getElementById("formServico");
  const btnSalvar = document.getElementById("btnSalvarServico");
  const inputId = document.getElementById("servicoId");
  const inputNome = document.getElementById("servicoNome");
  const inputPreco = document.getElementById("servicoPreco");
  const inputDesc = document.getElementById("servicoDesc");
  const tabelaContratos = document.getElementById("tabela-contratos-servicos");
  const filtroStatusContrato = document.getElementById("filtroStatusContrato");

  if (!dialog || !form || !btnSalvar) return;

   const showAlert = (options) => {
     if (window.Swal) return window.Swal.fire(options);
     console.log(options.title || options.text || "");
     return Promise.resolve();
   };

  function resetBorders() {
    [inputNome, inputPreco].forEach((el) => {
      if (el) el.style.borderColor = "#ced4da";
    });
  }

  function openDialog() {
    dialog.classList.add("adm-dialog--open");
  }

  function closeDialog() {
    dialog.classList.remove("adm-dialog--open");
  }

  async function salvarServico() {
    resetBorders();
    const nome = inputNome.value.trim();
    const preco = inputPreco.value.trim();
    const descricao = inputDesc.value.trim();
    const id = inputId.value.trim();

    const faltando = [];
    if (!nome) faltando.push(inputNome);
    if (!preco) faltando.push(inputPreco);
    if (faltando.length) {
      faltando.forEach((el) => (el.style.borderColor = "red"));
      showAlert({ icon: "warning", title: "Preencha Nome e Preço." });
      return;
    }

    const payload = { nome, preco, descricao };
    const isEdicao = Boolean(id);
    const url = isEdicao ? `/dashboard/services/${id}` : "/dashboard/services";
    const method = isEdicao ? "PUT" : "POST";

    btnSalvar.disabled = true;
    btnSalvar.classList.add("is-loading");

    try {
      const resposta = await fetch(url, {
        method,
        headers: { "Content-Type": "application/json", Accept: "application/json" },
        body: JSON.stringify(payload),
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Serviço salvo." });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao salvar serviço." });
      }
    } catch (err) {
      console.error(err);
      await showAlert({ icon: "error", title: "Erro ao salvar serviço. Tente novamente." });
    } finally {
      btnSalvar.disabled = false;
      btnSalvar.classList.remove("is-loading");
    }
  }

  async function excluirServico(btn) {
    const id = btn.dataset.id;
    const nome = btn.dataset.nome || "este serviço";
    if (!id) return;

    const confirma = window.Swal
      ? await window.Swal.fire({
          title: "Excluir serviço?",
          html: `Você está prestes a excluir <strong>${nome}</strong>.<br>Essa ação é irreversível.`,
          icon: "warning",
          showCancelButton: true,
          confirmButtonText: '<i class="fa-solid fa-trash"></i> Excluir',
          cancelButtonText: "Cancelar",
          confirmButtonColor: "#cc0000",
          cancelButtonColor: "#6b7280",
          reverseButtons: true,
          focusCancel: true,
        })
      : { isConfirmed: window.confirm("Excluir este serviço?") };

    if (!confirma.isConfirmed) return;

    btn.disabled = true;
    try {
      const resposta = await fetch(`/dashboard/services/${id}`, {
        method: "DELETE",
        headers: { Accept: "application/json" },
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Serviço excluído." });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao excluir serviço." });
      }
    } catch (err) {
      console.error(err);
      await showAlert({ icon: "error", title: "Erro ao excluir serviço. Tente novamente." });
    } finally {
      btn.disabled = false;
    }
  }

  btnSalvar.addEventListener("click", function (e) {
    e.preventDefault();
    salvarServico();
  });

  window.editarServico = function (btn) {
    inputId.value = btn.dataset.id || "";
    inputNome.value = btn.dataset.nome || "";
    inputPreco.value = btn.dataset.preco || "";
    inputDesc.value = btn.dataset.descricao || "";
    openDialog();
  };

  window.excluirServico = function (btn) {
    excluirServico(btn);
  };

  // ----- Gestão de contratos de serviços (admin) -----
  async function atualizarContrato(row) {
    const id = row?.dataset?.contratoId;
    if (!id) return;

    const statusSelect = row.querySelector(".js-contrato-status");
    const obsInput = row.querySelector(".js-contrato-obs");
    const status = statusSelect?.value;
    const observacoes = obsInput?.value?.trim() || null;

    const btn = row.querySelector(".js-atualizar-contrato");
    if (btn) {
      btn.disabled = true;
      btn.classList.add("is-loading");
    }

    try {
      const resposta = await fetch(`/dashboard/services/contratos/${id}/status`, {
        method: "PUT",
        headers: { "Content-Type": "application/json", Accept: "application/json" },
        body: JSON.stringify({ status, observacoes }),
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        if (window.Swal) {
          window.Swal.fire({
            toast: true,
            position: "top-end",
            timer: 2000,
            showConfirmButton: false,
            icon: "success",
            title: corpo.msg || "Status atualizado",
          });
        } else {
          await showAlert({ icon: "success", title: corpo.msg || "Status atualizado." });
        }
        row.dataset.status = status;
      } else {
        if (window.Swal) {
          window.Swal.fire({ icon: "error", title: "Erro", text: corpo.msg || "Erro ao atualizar status." });
        } else {
          await showAlert({ icon: "error", title: corpo.msg || "Erro ao atualizar status." });
        }
      }
    } catch (err) {
      console.error(err);
      if (window.Swal) {
        window.Swal.fire({ icon: "error", title: "Erro", text: "Erro ao atualizar status. Tente novamente." });
      } else {
        await showAlert({ icon: "error", title: "Erro ao atualizar status. Tente novamente." });
      }
    } finally {
      if (btn) {
        btn.disabled = false;
        btn.classList.remove("is-loading");
      }
    }
  }

  function filtrarContratos() {
    if (!tabelaContratos) return;
    const statusFiltro = filtroStatusContrato?.value || "";
    const linhas = tabelaContratos.querySelectorAll("tbody tr");
    linhas.forEach((tr) => {
      const status = tr.dataset.status || "";
      tr.style.display = !statusFiltro || status === statusFiltro ? "table-row" : "none";
    });
  }

  function syncStatusClasses(select) {
    if (!select) return;
    select.className = "adm-input adm-select-status js-contrato-status status-" + (select.value || "");
  }

  if (tabelaContratos) {
    // inicializa classes de status
    tabelaContratos.querySelectorAll(".js-contrato-status").forEach(syncStatusClasses);

    tabelaContratos.addEventListener("click", function (e) {
      const btn = e.target.closest(".js-atualizar-contrato");
      if (!btn) return;
      const row = btn.closest("tr");
      atualizarContrato(row);
    });

    tabelaContratos.addEventListener("change", function (e) {
      const select = e.target.closest(".js-contrato-status");
      if (select) {
        const row = select.closest("tr");
        if (row) row.dataset.status = select.value;
        syncStatusClasses(select);
        filtrarContratos();
      }
    });
  }

  if (filtroStatusContrato) {
    filtroStatusContrato.addEventListener("change", filtrarContratos);
  }
});
