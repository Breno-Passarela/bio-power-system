// ─────────────────────────────────────────────────────────────────────────────
// Bio-Power — register.js
// Contém: validação por etapa, stepper, CEP (ViaCEP), força da senha, máscaras
// ─────────────────────────────────────────────────────────────────────────────

// ─── Objeto de dados do formulário ──────────────────────────────────────────
const form = {
  nome: "",
  sobrenome: "",
  cpf: "",
  genero: "",
  email: "",
  telefone: "",
  data: "",
  estadoCivil: "",
  cep: "",
  cidade: "",
  estado: "",
  bairro: "",
  rua: "",
  numero: "",
  complemento: "",
  senha: "",
  confirmarSenha: "",
};

const fieldOrder = [
  "nome", "sobrenome", "cpf", "genero", "email", "telefone",
  "data", "estadoCivil",
  "cep", "cidade", "estado", "bairro", "rua", "numero", "complemento",
  "senha", "confirmarSenha",
];

// Campos por etapa — usados na validação parcial
const stepFields = {
  1: ["nome", "sobrenome", "cpf", "genero", "email", "telefone", "data", "estadoCivil"],
  2: ["cep", "cidade", "estado", "bairro", "rua", "numero", "complemento"],
  3: ["senha", "confirmarSenha"],
};

// Mapeamento campo → etapa (para navegar ao erro correto)
const fieldStepMap = {};
Object.entries(stepFields).forEach(([step, fields]) =>
  fields.forEach((f) => (fieldStepMap[f] = Number(step)))
);

const NAME_MIN_LENGTH = 3;
const NAME_REGEX = /^[A-Za-zÀ-ÿ]+(?: [A-Za-zÀ-ÿ]+)*$/;
const CITY_REGEX = /^[A-Za-zÀ-ÿ]+(?:[\s'-][A-Za-zÀ-ÿ]+)*$/;
const STREET_REGEX = /^[A-Za-zÀ-ÿ0-9]+(?:[\s.'-][A-Za-zÀ-ÿ0-9]+)*$/;
const PASSWORD_REGEX = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
const EMAIL_REGEX = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

function isValidCPF(cpf) {
  if (!cpf || cpf.length !== 11) return false;
  if (/^(\d)\1{10}$/.test(cpf)) return false;

  let sum = 0;
  for (let i = 0; i < 9; i++) {
    sum += parseInt(cpf.charAt(i)) * (10 - i);
  }

  let firstDigit = (sum * 10) % 11;
  if (firstDigit === 10) firstDigit = 0;
  if (firstDigit !== parseInt(cpf.charAt(9))) return false;

  sum = 0;
  for (let i = 0; i < 10; i++) {
    sum += parseInt(cpf.charAt(i)) * (11 - i);
  }

  let secondDigit = (sum * 10) % 11;
  if (secondDigit === 10) secondDigit = 0;

  return secondDigit === parseInt(cpf.charAt(10));
}

function isValidCEP(cep) {
  return /^\d{8}$/.test(cep);
}

function buildErrorList(errors) {
  const ul = document.createElement("ul");
  ul.classList.add("mb-0", "ps-3");
  errors.forEach(err => {
    const li = document.createElement("li");
    li.textContent = err;
    ul.appendChild(li);
  });
  return ul;
}

function setFieldError(fieldId, message) {
  const element = document.getElementById(fieldId);
  const feedback = document.getElementById(`error-${fieldId}`);
  if (!element || !feedback) return;

  feedback.innerHTML = "";

  if (message) {
    element.classList.add("is-invalid");

    if (Array.isArray(message)) {
      const ul = buildErrorList(message);
      feedback.appendChild(ul);
    } else {
      const ul = buildErrorList([message]);
      feedback.appendChild(ul);
    }

    feedback.style.display = "flex";
  } else {
    element.classList.remove("is-invalid");
    feedback.style.display = "none";
  }
}

function clearErrors() {
  fieldOrder.forEach((f) => setFieldError(f, null));
  const termsFb = document.getElementById("error-terms");
  if (termsFb) { termsFb.innerHTML = ""; termsFb.style.display = "none"; }
  document.getElementById("termsCheck")?.classList.remove("is-invalid");
}

function applyMasks() {
  const cpf = document.getElementById("cpf");
  const tel = document.getElementById("telefone");
  const cep = document.getElementById("cep");
  cpf?.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 11);
    v = v.replace(/(\d{3})(\d)/, "$1.$2");
    v = v.replace(/(\d{3})(\d)/, "$1.$2");
    v = v.replace(/(\d{3})(\d{1,2})$/, "$1-$2");
    e.target.value = v;
  });

  tel?.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 11);
    if (v.length > 6)
      v = v.replace(/^(\d{2})(\d{5})(\d{1,4})$/, "($1) $2-$3");
    else if (v.length > 2)
      v = v.replace(/^(\d{2})(\d{1,4})$/, "($1) $2");
    else if (v.length > 0)
      v = v.replace(/^(\d{1,2})$/, "($1");
    e.target.value = v;
  });

  cep?.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 8);
    v = v.replace(/(\d{5})(\d{1,3})$/, "$1-$2");
    e.target.value = v;
  });
}

function normalizeSpaces(str) {
  return str.trim().split(" ").filter((e) => e != "").join(" ");
}

function collectFormValues() {
  form.nome = normalizeSpaces(document.getElementById('nome')?.value || "");
  form.sobrenome = normalizeSpaces(document.getElementById('sobrenome')?.value || "");
  form.cpf = document.getElementById("cpf")?.value || "";
  form.genero = document.getElementById("genero")?.value || "";
  form.email = normalizeSpaces(document.getElementById("email")?.value || "");
  form.telefone = document.getElementById("telefone")?.value || "";
  form.data = document.getElementById("data")?.value || "";
  form.estadoCivil = document.getElementById("estadoCivil")?.value || "";
  form.cep = document.getElementById("cep")?.value || "";
  form.cidade = normalizeSpaces(document.getElementById("cidade")?.value || "");
  form.estado = document.getElementById("estado")?.value || "";
  form.bairro = normalizeSpaces(document.getElementById("bairro")?.value || "");
  form.rua = normalizeSpaces(document.getElementById("rua")?.value || "");
  form.numero = document.getElementById("numero")?.value || "";
  form.complemento = normalizeSpaces(document.getElementById("complemento")?.value || "");
  form.senha = document.getElementById("senha")?.value || "";
  form.confirmarSenha = document.getElementById("confirmarSenha")?.value || "";
}

function validateFields() {
  const errors = {};

  let rawCPF = form.cpf.replace(/\D/g, "");
  let rawTelefone = form.telefone.replace(/\D/g, "");
  let rawCEP = form.cep.replace(/\D/g, "");

  // NOME
  errors.nome = [];
  if (!form.nome) {
    errors.nome.push("Informe o nome");
  } else {
    if (form.nome.length < NAME_MIN_LENGTH)
      errors.nome.push(`Nome deve ter pelo menos ${NAME_MIN_LENGTH} caracteres.`);

    if (!NAME_REGEX.test(form.nome))
      errors.nome.push("Nome deve conter apenas letras e espaços simples");
  }
  if (errors.nome.length === 0) delete errors.nome;

  // SOBRENOME
  errors.sobrenome = [];
  if (!form.sobrenome) {
    errors.sobrenome.push("Informe o sobrenome");
  } else {
    if (form.sobrenome.length < NAME_MIN_LENGTH)
      errors.sobrenome.push(`Sobrenome deve ter pelo menos ${NAME_MIN_LENGTH} caracteres.`);

    if (!NAME_REGEX.test(form.sobrenome))
      errors.sobrenome.push("Sobrenome deve conter apenas letras e espaços simples");
  }
  if (errors.sobrenome.length === 0) delete errors.sobrenome;

  // EMAIL
  errors.email = [];
  if (!form.email) {
    errors.email.push("Informe o e-mail");
  } else {
    if (!EMAIL_REGEX.test(form.email))
      errors.email.push("Informe um e-mail válido");
  }
  if (errors.email.length === 0) delete errors.email;

  // SENHA
  errors.senha = [];
  if (!form.senha) {
    errors.senha.push("Informe a senha");
  } else {
    if (!PASSWORD_REGEX.test(form.senha))
      errors.senha.push(
        "A senha precisa ter 8 caracteres, incluindo letra maiúscula, minúscula, número e símbolo"
      );
  }
  if (errors.senha.length === 0) delete errors.senha;

  // TELEFONE
  errors.telefone = [];
  if (!rawTelefone) {
    errors.telefone.push("Informe o telefone");
  } else {
    if (!/^([1-9]{2})(9\d{8}|\d{8})$/.test(rawTelefone))
      errors.telefone.push("Telefone inválido");
  }
  if (errors.telefone.length === 0) delete errors.telefone;

  // CPF
  errors.cpf = [];
  if (!rawCPF) {
    errors.cpf.push("Informe o CPF");
  } else {
    if (!isValidCPF(rawCPF))
      errors.cpf.push("CPF inválido");
  }
  if (errors.cpf.length === 0) delete errors.cpf;

  // CEP
  errors.cep = [];
  if (!rawCEP) {
    errors.cep.push("Informe o CEP");
  } else {
    if (!isValidCEP(rawCEP))
      errors.cep.push("CEP inválido");
  }
  if (errors.cep.length === 0) delete errors.cep;

  // CIDADE
  errors.cidade = [];
  if (!form.cidade) {
    errors.cidade.push("Informe a cidade");
  } else {
    if (form.cidade.length < 3)
      errors.cidade.push("Cidade muito curta");

    if (!CITY_REGEX.test(form.cidade))
      errors.cidade.push("Cidade inválida");
  }
  if (errors.cidade.length === 0) delete errors.cidade;

  // ESTADO (select)
  errors.estado = [];
  if (!form.estado) errors.estado.push("Selecione o estado");
  if (errors.estado.length === 0) delete errors.estado;

  // BAIRRO
  errors.bairro = [];
  if (!form.bairro) {
    errors.bairro.push("Informe o bairro");
  } else {
    if (form.bairro.length < 3)
      errors.bairro.push("Bairro inválido");
  }
  if (errors.bairro.length === 0) delete errors.bairro;

  // RUA
  errors.rua = [];
  if (!form.rua) {
    errors.rua.push("Informe o endereço");
  } else {
    if (!STREET_REGEX.test(form.rua))
      errors.rua.push("Endereço inválido");
  }
  if (errors.rua.length === 0) delete errors.rua;

  // NUMERO
  errors.numero = [];
  if (!form.numero) {
    errors.numero.push("Informe o número");
  } else {
    if (!/^\d+$/.test(form.numero) && !/^s\/?n$/i.test(form.numero))
      errors.numero.push('Use apenas números ou "S/N"');
  }
  if (errors.numero.length === 0) delete errors.numero;

  // COMPLEMENTO
  errors.complemento = [];
  if (form.complemento.length > 120)
    errors.complemento.push("Complemento deve ter até 120 caracteres");
  if (errors.complemento.length === 0) delete errors.complemento;

  // DATA
  errors.data = [];
  if (!form.data) {
    errors.data.push("Informe a data");
  } else {
    const birth = new Date(`${form.data}T00:00:00`);
    if (Number.isNaN(birth.getTime()))
      errors.data.push("Data inválida");
    else if (birth > new Date())
      errors.data.push("Data futura não permitida");
  }
  if (errors.data.length === 0) delete errors.data;

  // GÊNERO
  errors.genero = [];
  if (!form.genero)
    errors.genero.push("Selecione o gênero");
  if (errors.genero.length === 0) delete errors.genero;

  // ESTADO CIVIL
  errors.estadoCivil = [];
  if (!form.estadoCivil)
    errors.estadoCivil.push("Selecione o estado civil");
  if (errors.estadoCivil.length === 0) delete errors.estadoCivil;

  // CONFIRMAR SENHA
  errors.confirmarSenha = [];
  if (!form.confirmarSenha) {
    errors.confirmarSenha.push("Confirme a senha");
  } else if (form.senha !== form.confirmarSenha) {
    errors.confirmarSenha.push("As senhas não coincidem");
  }
  if (errors.confirmarSenha.length === 0) delete errors.confirmarSenha;

  return errors;
}

// Valida apenas os campos de uma etapa específica
function validateStep(stepNum) {
  collectFormValues();
  const allErrors = validateFields();
  const stepErr = {};
  (stepFields[stepNum] || []).forEach((f) => {
    if (allErrors[f]) stepErr[f] = allErrors[f];
  });
  return stepErr;
}

// Limpar campos no load
window.addEventListener("load", () => {
  fieldOrder.forEach(field => {
    const input = document.getElementById(field);
    if (!input) return;
    input.value = "";
    input.classList.remove("readonly-style", "is-invalid");
    const feedback = document.getElementById(`error-${field}`);
    if (feedback) {
      feedback.textContent = "";
      feedback.style.display = "none";
    }
  });
});

// ─── Toggle senha ────────────────────────────────────────────────────────────
function passwordShow(toggleId, inputId) {
  const toggle = document.getElementById(toggleId);
  const input = document.getElementById(inputId);
  if (!toggle || !input) return;
  if (input.type === "password") {
    input.type = "text";
    toggle.classList.replace("fa-eye", "fa-eye-slash");
  } else {
    input.type = "password";
    toggle.classList.replace("fa-eye-slash", "fa-eye");
  }
}

// ─── Força da senha + checklist ───────────────────────────────────────────────
function initPasswordStrength() {
  const senhaInput = document.getElementById("senha");
  const strengthBar = document.getElementById("passStrengthWrap");
  const fill = document.getElementById("passStrengthFill");
  const labelEl = document.getElementById("passStrengthLabel");
  if (!senhaInput) return;

  const reqs = {
    length: { el: document.getElementById("req-length"), test: (v) => v.length >= 8 },
    upper: { el: document.getElementById("req-upper"), test: (v) => /[A-Z]/.test(v) },
    lower: { el: document.getElementById("req-lower"), test: (v) => /[a-z]/.test(v) },
    number: { el: document.getElementById("req-number"), test: (v) => /[0-9]/.test(v) },
    symbol: { el: document.getElementById("req-symbol"), test: (v) => /[^A-Za-z0-9]/.test(v) },
  };

  senhaInput.addEventListener("input", () => {
    const v = senhaInput.value;
    let score = 0;
    Object.values(reqs).forEach((r) => {
      if (!r.el) return;
      const ok = r.test(v);
      if (ok) score++;
      r.el.classList.toggle("req-ok", ok);
      r.el.classList.toggle("req-fail", v.length > 0 && !ok);
      r.el.querySelector("i").className = ok ? "fas fa-check-circle" : "fas fa-circle";
    });
    if (!v) { strengthBar?.classList.add("d-none"); return; }
    strengthBar?.classList.remove("d-none");
    const levels = [
      { pct: "20%", color: "#ef3538", text: "Muito fraca" },
      { pct: "40%", color: "#ef3538", text: "Fraca" },
      { pct: "60%", color: "#f5a623", text: "Razoável" },
      { pct: "80%", color: "#4caf50", text: "Boa" },
      { pct: "100%", color: "#2e7d32", text: "Forte" },
    ];
    const lvl = levels[score - 1] || levels[0];
    if (fill) { fill.style.width = lvl.pct; fill.style.background = lvl.color; }
    if (labelEl) { labelEl.textContent = lvl.text; labelEl.style.color = lvl.color; }
  });
}

// ─── Stepper ──────────────────────────────────────────────────────────────────
let _currentStep = 1;

function _updateProgress(step) {
  const labels = [
    "Etapa 1 de 3 — Dados Pessoais",
    "Etapa 2 de 3 — Endereço",
    "Etapa 3 de 3 — Senha",
  ];
  const pcts = ["33%", "66%", "100%"];
  const fill = document.getElementById("stepProgressFill");
  const label = document.getElementById("stepProgressLabel");
  if (fill) fill.style.width = pcts[step - 1];
  if (label) label.textContent = labels[step - 1];
  document.getElementById("line-1-2")?.classList.toggle("completed", step >= 2);
  document.getElementById("line-2-3")?.classList.toggle("completed", step >= 3);
}

function _goToStep(step) {
  document.getElementById("step-" + _currentStep)?.classList.add("d-none");
  document.getElementById("step-item-" + _currentStep)?.classList.remove("active");
  document.getElementById("step-item-" + _currentStep)?.classList.add("completed");
  _currentStep = step;
  const panel = document.getElementById("step-" + _currentStep);
  if (panel) {
    panel.classList.remove("d-none");
    panel.classList.add("step-enter");
    setTimeout(() => panel.classList.remove("step-enter"), 350);
  }
  document.getElementById("step-item-" + _currentStep)?.classList.add("active");
  panel?.scrollIntoView({ behavior: "smooth", block: "start" });
  _updateProgress(_currentStep);
}

function _goBack(step) {
  document.getElementById("step-" + _currentStep)?.classList.add("d-none");
  document.getElementById("step-item-" + _currentStep)?.classList.remove("active");
  _currentStep = step;
  document.getElementById("step-" + _currentStep)?.classList.remove("d-none");
  document.getElementById("step-item-" + _currentStep)?.classList.remove("completed");
  document.getElementById("step-item-" + _currentStep)?.classList.add("active");
  _updateProgress(_currentStep);
}

function _focusFirstFieldError(stepErr, stepNum) {
  const firstField = (stepFields[stepNum] || []).find((f) => stepErr[f]);
  if (!firstField) return;
  const el = document.getElementById(firstField);
  if (!el) return;
  el.scrollIntoView({ behavior: "smooth", block: "center" });
  setTimeout(() => el.focus(), 300);
}

function initStepper() {
  document.getElementById("next-1")?.addEventListener("click", () => {
    const stepErr = validateStep(1);
    if (Object.keys(stepErr).length) {
      Object.entries(stepErr).forEach(([f, msg]) => setFieldError(f, msg));
      _focusFirstFieldError(stepErr, 1);
      return;
    }
    stepFields[1].forEach((f) => setFieldError(f, null));
    _goToStep(2);
  });

  document.getElementById("next-2")?.addEventListener("click", () => {
    const stepErr = validateStep(2);
    if (Object.keys(stepErr).length) {
      Object.entries(stepErr).forEach(([f, msg]) => setFieldError(f, msg));
      _focusFirstFieldError(stepErr, 2);
      return;
    }
    stepFields[2].forEach((f) => setFieldError(f, null));
    _goToStep(3);
  });

  document.getElementById("back-2")?.addEventListener("click", () => _goBack(1));
  document.getElementById("back-3")?.addEventListener("click", () => _goBack(2));
}

// ─── CEP — ViaCEP ─────────────────────────────────────────────────────────────
function initCepLookup() {
  const cepInput = document.getElementById("cep");
  if (!cepInput) return;

  cepInput.addEventListener("blur", async function () {
    const digits = this.value.replace(/\D/g, "");
    if (!digits) return;
    if (!isValidCEP(digits)) { setFieldError("cep", "CEP inválido."); return; }

    this.disabled = true;
    try {
      const res = await fetch(`https://viacep.com.br/ws/${digits}/json/`);
      if (!res.ok) throw new Error();
      const data = await res.json();
      if (data.erro) throw new Error("não encontrado");

      const mapa = { cidade: data.localidade || "", bairro: data.bairro || "", rua: data.logradouro || "" };
      Object.entries(mapa).forEach(([id, val]) => {
        const el = document.getElementById(id);
        if (!el) return;
        el.value = val;
        el.classList.add("readonly-style");
        if (val) setFieldError(id, null);
      });

      const estadoSelect = document.getElementById("estado");
      if (estadoSelect && data.uf) {
        estadoSelect.value = data.uf.toUpperCase();
        estadoSelect.classList.add("readonly-style");
        setFieldError("estado", null);
      }

      setFieldError("cep", null);
      document.getElementById("numero")?.focus();
    } catch {
      setFieldError("cep", "Não foi possível localizar o CEP informado.");
    } finally {
      this.disabled = false;
    }
  });

  // Limpa campos ao apagar o CEP
  cepInput.addEventListener("input", function () {
    if (!this.value) {
      ["cidade", "bairro", "rua", "estado"].forEach((id) => {
        const el = document.getElementById(id);
        if (!el) return;
        el.value = "";
        el.classList.remove("readonly-style");
      });
    }
  });
}

// ─── Inicialização ────────────────────────────────────────────────────────────
document.addEventListener("DOMContentLoaded", () => {
  // Logo mobile
  document.getElementById("img-logo-mobile")?.addEventListener("click", () => {
    window.location.href = "/";
  });

  applyMasks();
  initCepLookup();
  initPasswordStrength();
  initStepper();

  const formEl = document.getElementById("registerForm");
  if (!formEl) return;

  formEl.addEventListener("submit", (event) => {
    event.preventDefault();
    clearErrors();
    collectFormValues();
    const errors = validateFields();

    // Termos de uso
    const termsEl = document.getElementById("termsCheck");
    if (termsEl && !termsEl.checked) {
      errors.terms = ["Você precisa aceitar os Termos de Uso"];
      termsEl.classList.add("is-invalid");
      const termsFb = document.getElementById("error-terms");
      if (termsFb) {
        termsFb.appendChild(buildErrorList(errors.terms));
        termsFb.style.display = "flex";
      }
    }

    Object.entries(errors).forEach(([f, msg]) => {
      if (f !== "terms") setFieldError(f, msg);
    });

    if (Object.keys(errors).length === 0) { formEl.submit(); return; }

    // Navega à etapa do primeiro erro e foca o campo
    const firstErrField = fieldOrder.find((f) => errors[f]);
    if (firstErrField) {
      const targetStep = fieldStepMap[firstErrField] || _currentStep;
      if (targetStep !== _currentStep) _goToStep(targetStep);
      requestAnimationFrame(() => {
        const el = document.getElementById(firstErrField);
        if (!el) return;
        el.scrollIntoView({ behavior: "smooth", block: "center" });
        setTimeout(() => el.focus(), 300);
      });
    }
  });
});