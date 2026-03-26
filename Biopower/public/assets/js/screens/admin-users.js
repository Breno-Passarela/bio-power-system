document.addEventListener("DOMContentLoaded", function () {
  const dialog = document.getElementById("dialog-usuario");
  const form = document.getElementById("formUsuario");
  const btnSalvar = document.getElementById("btnSalvarUsuario");
  const inputId = document.getElementById("usuarioId");
  const inputNome = document.getElementById("usuarioNome");
  const inputEmail = document.getElementById("usuarioEmail");
  const inputSenha = document.getElementById("usuarioSenha");
  const inputCpf = document.getElementById("usuarioCpf");
  const inputTipo = document.getElementById("usuarioTipo");
  const inputAtivo = document.getElementById("usuarioAtivo");
  const senhaHint = document.getElementById("senhaHint");
  const btnNovoUsuario = document.getElementById("btnNovoUsuario");

  const showAlert = (options) => {
    if (window.Swal) return window.Swal.fire(options);
    console.log(options.title || options.text || "");
    return Promise.resolve();
  };

  if (!dialog || !form || !btnSalvar) return;

  function resetBorders() {
    [inputNome, inputEmail, inputSenha, inputCpf, inputTipo, inputAtivo]
      .filter(Boolean)
      .forEach((el) => (el.style.borderColor = "#ced4da"));
  }

  function openDialog() {
    if (dialog) dialog.classList.add("adm-dialog--open");
  }

  function closeDialog() {
    if (dialog) dialog.classList.remove("adm-dialog--open");
  }

  function preencherCampos(dados) {
    inputId.value = dados?.id || "";
    inputNome.value = dados?.nome || "";
    inputEmail.value = dados?.email || "";
    inputSenha.value = "";
    inputCpf.value = dados?.cpf || "";
    inputTipo.value = dados?.tipo || "";
    inputAtivo.value = dados?.ativo != null ? String(dados.ativo) : "1";
    senhaHint.textContent = dados?.id ? "(preencha para alterar)" : "*";
  }

  function coletarPayload() {
    return {
      nome: inputNome.value.trim(),
      email: inputEmail.value.trim().toLowerCase(),
      senha: inputSenha.value.trim(),
      cpfCnpj: inputCpf.value.trim() || null,
      typeId: inputTipo.value,
      ativo: inputAtivo.value,
    };
  }

  function validar(payload, isEdicao) {
    resetBorders();
    const faltando = [];
    if (!payload.nome) faltando.push(inputNome);
    if (!payload.email) faltando.push(inputEmail);
    if (!payload.typeId) faltando.push(inputTipo);
    if (!isEdicao && !payload.senha) faltando.push(inputSenha);

    if (faltando.length) {
      const msgObrigatorio = isEdicao
        ? "Preencha os campos obrigatorios (Nome, Email e Perfil)."
        : "Preencha os campos obrigatorios (Nome, Email, Perfil e Senha).";
      faltando.forEach((el) => (el.style.borderColor = "red"));
      showAlert({ icon: "warning", title: msgObrigatorio });
      return false;
    }
    return true;
  }

  async function salvarUsuario() {
    const id = inputId.value.trim();
    const isEdicao = Boolean(id);
    const payload = coletarPayload();
    if (!isEdicao && payload.senha === "") payload.senha = undefined;
    if (!validar(payload, isEdicao)) return;

    // Evita enviar senha vazia em edicao
    if (isEdicao && !payload.senha) delete payload.senha;

    btnSalvar.disabled = true;
    btnSalvar.classList.add("is-loading");

    const url = isEdicao ? `/dashboard/users/${id}` : "/dashboard/users";
    const method = isEdicao ? "PUT" : "POST";

    try {
      const resposta = await fetch(url, {
        method,
        headers: { "Content-Type": "application/json", Accept: "application/json" },
        body: JSON.stringify(payload),
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Usuario salvo." });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao salvar usuario." });
      }
    } catch (err) {
      console.error(err);
      await showAlert({ icon: "error", title: "Erro ao salvar usuario. Tente novamente." });
    } finally {
      btnSalvar.disabled = false;
      btnSalvar.classList.remove("is-loading");
    }
  }

  async function deletarUsuario(btn) {
    const id = btn.dataset.id;
    const nome = btn.dataset.nome || "este usuario";
    if (!id) return;

    const confirmacao = window.Swal
      ? await window.Swal.fire({
          title: "Excluir usuario?",
          html: `Você está prestes a desativar <strong>${nome}</strong>.<br>Essa ação pode impedir o acesso ao sistema.` ,
          icon: "warning",
          showCancelButton: true,
          confirmButtonText: '<i class="fa-solid fa-trash"></i> Excluir',
          cancelButtonText: "Cancelar",
          confirmButtonColor: "#cc0000",
          cancelButtonColor: "#6b7280",
          reverseButtons: true,
          focusCancel: true,
        })
      : { isConfirmed: window.confirm("Excluir este usuario?") };

    if (!confirmacao.isConfirmed) return;

    btn.disabled = true;
    try {
      const resposta = await fetch(`/dashboard/users/${id}`, {
        method: "DELETE",
        headers: { Accept: "application/json" },
      });
      const corpo = await resposta.json().catch(() => ({ ok: false, msg: "Erro ao ler resposta." }));
      if (resposta.ok && corpo.ok) {
        await showAlert({ icon: "success", title: corpo.msg || "Usuario desativado." });
        window.location.reload();
      } else {
        await showAlert({ icon: "error", title: corpo.msg || "Erro ao desativar usuario." });
      }
    } catch (err) {
      console.error(err);
      await showAlert({ icon: "error", title: "Erro ao desativar usuario. Tente novamente." });
    } finally {
      btn.disabled = false;
    }
  }

  btnSalvar.addEventListener("click", function (e) {
    e.preventDefault();
    salvarUsuario();
  });

  if (btnNovoUsuario) {
    btnNovoUsuario.addEventListener("click", function () {
      preencherCampos({});
      resetBorders();
      openDialog();
    });
  }

  document.querySelectorAll(".js-edit-user").forEach((btn) => {
    btn.addEventListener("click", function () {
      preencherCampos({
        id: btn.dataset.id,
        nome: btn.dataset.nome,
        email: btn.dataset.email,
        cpf: btn.dataset.cpf,
        tipo: btn.dataset.type,
        ativo: btn.dataset.ativo,
      });
      resetBorders();
      openDialog();
    });
  });

  document.querySelectorAll(".js-delete-user").forEach((btn) => {
    btn.addEventListener("click", function () {
      deletarUsuario(btn);
    });
  });

  // Expor para compatibilidade se necessario
  window.salvarUsuario = salvarUsuario;
  window.deletarUsuario = deletarUsuario;
  window.openDialogUsuario = openDialog;
  window.closeDialogUsuario = closeDialog;
});
