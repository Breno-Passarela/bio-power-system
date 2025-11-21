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
};

const fieldOrder = [
  "nome",
  "sobrenome",
  "cpf",
  "genero",
  "email",
  "telefone",
  "data",
  "estadoCivil",
  "cep",
  "cidade",
  "estado",
  "bairro",
  "rua",
  "numero",
  "complemento",
  "senha"
];

const requiredFields = [
    "nome",
    "sobrenome",
    "email",
    "senha",
    "data-nascimento",
    "cpf",
    "telefone",
    "cep",
    "rua",
    "numero",
    "bairro",
    "cidade",
    "estado"
];

const NAME_MIN_LENGTH     = 3;
const NAME_REGEX          = /^[A-Za-zÀ-ÿ]+(?: [A-Za-zÀ-ÿ]+)*$/;
const CITY_REGEX          = /^[A-Za-zÀ-ÿ]+(?:[\s'-][A-Za-zÀ-ÿ]+)*$/;
const STREET_REGEX        = /^[A-Za-zÀ-ÿ0-9]+(?:[\s.'-][A-Za-zÀ-ÿ0-9]+)*$/;
const PASSWORD_REGEX = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
const EMAIL_REGEX          = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

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
  fieldOrder.forEach(f => setFieldError(f, null));
}

function applyMasks() {
  const cpf = document.getElementById("cpf");
  const tel = document.getElementById("telefone");
  const cep = document.getElementById("cep");
  const uf = document.getElementById("estado");

  cpf.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 11);
    v = v.replace(/(\d{3})(\d)/, "$1.$2");
    v = v.replace(/(\d{3})(\d)/, "$1.$2");
    v = v.replace(/(\d{3})(\d{1,2})$/, "$1-$2");
    e.target.value = v;
  });

  tel.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 11);
    if (v.length > 6)
      v = v.replace(/^(\d{2})(\d{5})(\d{1,4})$/, "($1) $2-$3");
    else if (v.length > 2)
      v = v.replace(/^(\d{2})(\d{1,4})$/, "($1) $2");
    else if (v.length > 0)
      v = v.replace(/^(\d{1,2})$/, "($1");
    e.target.value = v;
  });

  cep.addEventListener("input", e => {
    let v = e.target.value.replace(/\D/g, "").slice(0, 8);
    v = v.replace(/(\d{5})(\d{1,3})$/, "$1-$2");
    e.target.value = v;
  });

  uf.addEventListener("input", e => {
    e.target.value = e.target.value.toUpperCase().replace(/[^A-Z]/g, "").slice(0, 2);
  });
}

function normalizeSpaces(str) {
  return str.trim().split(" ").filter(Boolean).join(" ");
}

function collectFormValues() {
  form.nome         = normalizeSpaces(document.getElementById('nome')?.value || "");
  form.sobrenome    = normalizeSpaces(document.getElementById('sobrenome')?.value || "");
  form.cpf          = document.getElementById("cpf")?.value || "";
  form.genero       = document.getElementById("genero")?.value || "";
  form.email        = normalizeSpaces(document.getElementById("email")?.value || "");
  form.telefone     = document.getElementById("telefone")?.value || "";
  form.data         = document.getElementById("data")?.value || "";
  form.estadoCivil  = document.getElementById("estadoCivil")?.value || "";
  form.cep          = document.getElementById("cep")?.value || "";
  form.cidade       = normalizeSpaces(document.getElementById("cidade")?.value || "");
  form.estado       = normalizeSpaces(document.getElementById("estado")?.value || "");
  form.bairro       = normalizeSpaces(document.getElementById("bairro")?.value || "");
  form.rua          = normalizeSpaces(document.getElementById("rua")?.value || "");
  form.numero       = document.getElementById("numero")?.value || "";
  form.complemento  = normalizeSpaces(document.getElementById("complemento")?.value || "");
  form.senha        = document.getElementById("senha")?.value || "";
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

  // ESTADO (UF)
  errors.estado = [];
  if (!form.estado) {
    errors.estado.push("Informe a UF");
  } else {
    if (!/^[A-Z]{2}$/.test(form.estado))
      errors.estado.push("UF inválida");
  }
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

  return errors;
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

window.addEventListener("load", updateRegisterButton());

// Função para mostrar senha
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

document.addEventListener("DOMContentLoaded", () => {
  applyMasks();

  const formEl = document.querySelector("form.needs-validation");

  formEl.addEventListener("submit", event => {
    event.preventDefault();

    clearErrors();
    collectFormValues();

    const errors = validateFields();

    Object.keys(errors).forEach(f => setFieldError(f, errors[f]));

    if (Object.keys(errors).length === 0) {
      formEl.submit();
    }
  });
});

const formEl = document.querySelector("form.needs-validation");

formEl.addEventListener("submit", event => {
  event.preventDefault();
  
  clearErrors();
  collectFormValues();
  const errors = validateFields();
  
  Object.keys(errors).forEach(f => setFieldError(f, errors[f]));
  
  if (Object.keys(errors).length === 0) {
    formEl.submit();
  }
});

// API CEP
document.getElementById("cep").addEventListener("blur", async function () {
  const cepDigits = this.value.replace(/\D/g, "");
  if (!cepDigits) return;

  if (!isValidCEP(cepDigits)) {
    setFieldError("cep", "CEP inválido.");
    return;
  }

  try {
    const response = await fetch(`https://brasilapi.com.br/api/cep/v1/${cepDigits}`);
    if (!response.ok) throw new Error("CEP não encontrado");

    const data = await response.json();
    const mapa = {
      estado: "state",
      cidade: "city",
      bairro: "neighborhood",
      rua: "street",
    };

    Object.keys(mapa).forEach(id => {
      const input = document.getElementById(id);
      input.value = data[mapa[id]] || "";
      input.classList.add("readonly-style");
      setFieldError(id, null);
    });

    document.getElementById("estado").value =
      document.getElementById("estado").value.toUpperCase();

    setFieldError("cep", null);
  } catch (error) {
    console.error(error);
    setFieldError("cep", "Não foi possível localizar o CEP.");
  }
});

function updateRegisterButton() {
  const registerButton = document.getElementById("btn-register");

  collectFormValues();
  const errors = validateFields();

  let allValid = true;

  requiredFields.forEach(field => {
    const input = document.getElementById(field);
    const isEmpty = !input || !input.value.trim();
    const hasError = errors.hasOwnProperty(field);

    if (isEmpty || hasError) {
      allValid = false;
    }
  });

  registerButton.disabled = !allValid;
}

requiredFields.forEach(field => {
  const input = document.getElementById(field);
  if (!input) return;

  input.addEventListener("input", updateRegisterButton);
  input.addEventListener("blur", updateRegisterButton);
});