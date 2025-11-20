const form = {
  nome: "",
  sobrenome: "",
  email: "",
  senha: "",
  telefone: "",
  cpf: "",
  endereco: "",
  numero: "",
  cep: "",
  data: "",
  genero: "",
  estado: "",
  cidade: "",
  bairro: "",
  estadoCivil: "",
  complemento: "",
};

const NAME_MIN_LENGTH = 3;
const NAME_REGEX = /^[A-Za-zÀ-ÿ]+(?: [A-Za-zÀ-ÿ]+)*$/;
const CITY_REGEX = /^[A-Za-zÀ-ÿ]+(?:[\s'-][A-Za-zÀ-ÿ]+)*$/;
const STREET_REGEX = /^[A-Za-zÀ-ÿ0-9]+(?:[\s.'-][A-Za-zÀ-ÿ0-9]+)*$/;
const ERROR_ICON_HTML = '<i class="fa-solid fa-circle-exclamation me-1"></i>';

document
  .getElementById("registerForm")
  .addEventListener("submit", function (event) {
    event.preventDefault();

    collectFormValues();
    clearErrors();
    const errors = validateFields();

    if (Object.keys(errors).length > 0) {
      showErrors(errors);
      return;
    }

    this.submit();
  });

function collectFormValues() {
  form.nome = normalizeSpaces(getId(nome));
  form.sobrenome = normalizeSpaces((sobrenomeInput?.value || ""));
  form.email = (document.getElementById("email")?.value || "");
  form.senha = (document.getElementById("senha")?.value || "");
  form.telefone = (document.getElementById("telefone")?.value || "");
  form.cpf = (document.getElementById("cpf")?.value || "");
  form.endereco = (document.getElementById("endereco")?.value || "");
  form.numero = (document.getElementById("numero")?.value || "");
  form.cep = (document.getElementById("cep")?.value || "");
  form.data = document.getElementById("data")?.value || "";
  form.genero = document.getElementById("genero")?.value || "";
  form.estado = ((estadoInput?.value || "").toUpperCase());
  form.cidade = normalizeSpaces((cidadeInput?.value || ""));
  form.bairro = normalizeSpaces((bairroInput?.value || ""));
  form.estadoCivil = document.getElementById("estadoCivil")?.value || "";
  form.complemento = (document.getElementById("complemento")?.value || "");
}

function validateFields() {
  const errors = {};
  const strongPasswordRegex =
    /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

  const rawCPF = form.cpf.replace(/\D/g, "");
  const rawTelefone = form.telefone.replace(/\D/g, "");
  const rawCEP = form.cep.replace(/\D/g, "");

  if (!form.nome) {
    errors.nome = "Informe o nome.";
  } else if (form.nome.length < NAME_MIN_LENGTH) {
    errors.nome = `Nome deve ter pelo menos ${NAME_MIN_LENGTH} caracteres.`;
  } else if (!NAME_REGEX.test(form.nome)) {
    errors.nome = "Nome deve conter apenas letras e espaços simples.";
  }

  if (!form.sobrenome) {
    errors.sobrenome = "Informe o sobrenome.";
  } else if (form.sobrenome.length < NAME_MIN_LENGTH) {
    errors.sobrenome = `Sobrenome deve ter pelo menos ${NAME_MIN_LENGTH} caracteres.`;
  } else if (!NAME_REGEX.test(form.sobrenome)) {
    errors.sobrenome = "Sobrenome deve conter apenas letras e espaços simples.";
  }

  if (!form.email) {
    errors.email = "Informe o e-mail.";
  } else if (!emailRegex.test(form.email)) {
    errors.email = "Informe um e-mail válido (ex.: nome@dominio.com).";
  }

  if (!form.senha) {
    errors.senha = "Informe a senha.";
  } else if (!strongPasswordRegex.test(form.senha)) {
    errors.senha =
      "A senha precisa ter 8 caracteres, incluindo letra maiúscula, minúscula, número e símbolo.";
  }

  if (!rawTelefone) {
    errors.telefone = "Informe o telefone.";
  } else if (
    !/^([1-9]{2})(9\d{8}|\d{8})$/.test(rawTelefone) ||
    /^(\d)\1{9,10}$/.test(rawTelefone)
  ) {
    errors.telefone =
      "Informe um telefone válido com DDD (ex.: (11) 90000-0000).";
  }

  if (!rawCPF) {
    errors.cpf = "Informe o CPF.";
  } else if (!isValidCPF(rawCPF)) {
    errors.cpf = "Informe um CPF válido.";
  }

  if (!form.endereco) {
    errors.endereco = "Informe o logradouro.";
  } else if (!STREET_REGEX.test(form.endereco)) {
    errors.endereco =
      "Endereço deve conter letras, números e separadores simples.";
  }

  if (!form.numero) {
    errors.numero = "Informe o número do endereço.";
  } else if (
    !/^\d+$/.test(form.numero) &&
    !/^s\/?n$/i.test(form.numero)
  ) {
    errors.numero = 'Use apenas dígitos ou "S/N".';
  }

  if (!rawCEP) {
    errors.cep = "Informe o CEP.";
  } else if (!isValidCEP(rawCEP)) {
    errors.cep = "Informe um CEP válido (00000-000).";
  }

  if (!form.data) {
    errors.data = "Informe a data de nascimento.";
  } else {
    const birthDate = new Date(`${form.data}T00:00:00`);
    if (Number.isNaN(birthDate.getTime())) {
      errors.data = "Informe uma data de nascimento válida.";
    } else if (birthDate > new Date()) {
      errors.data = "Data de nascimento não pode ser futura.";
  }

  if (!form.genero) {
    errors.genero = "Selecione uma opção de gênero biológico.";
  }

  if (!form.estadoCivil) {
    errors.estadoCivil = "Selecione o estado civil.";
  }

  if (!form.cidade) {
    errors.cidade = "Informe a cidade.";
  } else if (form.cidade.length < 3 || !CITY_REGEX.test(form.cidade)) {
    errors.cidade =
      "Cidade deve conter apenas letras e separadores simples.";
  }

  if (!form.estado) {
    errors.estado = "Informe a sigla do estado.";
  } else if (!/^[A-Z]{2}$/.test(form.estado)) {
    errors.estado = "Informe a sigla do estado (ex.: SP).";
  }

  if (!form.bairro) {
    errors.bairro = "Informe o bairro.";
  } else if (form.bairro.length < 3) {
    errors.bairro = "Bairro deve ter ao menos 3 caracteres.";
  }

  if (form.complemento.length > 120) {
    errors.complemento = "Complemento deve ter até 120 caracteres.";
  }

  return errors;
}

function showErrors(errors) {
  Object.entries(errors).forEach(([field, message]) => {
    setFieldError(field, message);
  });

  const [firstError] = Object.keys(errors);
  if (firstError) {
    const element = document.getElementById(firstError);
    if (element) element.focus();
  }
}

function clearErrors() {
  fieldOrder.forEach((field) => setFieldError(field, null));
}

function setFieldError(fieldId, message) {
  const element = document.getElementById(fieldId);
  const feedback = document.getElementById(`error-${fieldId}`);
  if (!element || !feedback) return;

  const inputGroup = element.closest(".floating-input-group");

  if (message) {
    element.classList.add("is-invalid");
    element.setAttribute("aria-invalid", "true");
    if (inputGroup) inputGroup.classList.add("has-error");
    feedback.innerHTML = `${ERROR_ICON_HTML}<span>${message}</span>`;
    feedback.style.display = "flex";
  } else {
    element.classList.remove("is-invalid");
    element.removeAttribute("aria-invalid");
    if (inputGroup) inputGroup.classList.remove("has-error");
    feedback.innerHTML = "";
    feedback.style.display = "none";
  }
}

function isValidCPF(cpf) {
  if (!cpf || cpf.length !== 11) return false;
  if (/^(\d)\1{10}$/.test(cpf)) return false;

  let sum = 0;
  for (let i = 0; i < 9; i += 1) {
    sum += parseInt(cpf.charAt(i), 10) * (10 - i);
  }
  let firstDigit = (sum * 10) % 11;
  if (firstDigit === 10) firstDigit = 0;
  if (firstDigit !== parseInt(cpf.charAt(9), 10)) return false;

  sum = 0;
  for (let i = 0; i < 10; i += 1) {
    sum += parseInt(cpf.charAt(i), 10) * (11 - i);
  }
  let secondDigit = (sum * 10) % 11;
  if (secondDigit === 10) secondDigit = 0;
  return secondDigit === parseInt(cpf.charAt(10), 10);
}

function isValidCEP(cep) {
  return /^\d{8}$/.test(cep);
}

// Máscaras

document.getElementById("cep").addEventListener("input", function () {
  let value = this.value.replace(/\D/g, "").slice(0, 8);
  this.value =
    value.length > 5 ? value.replace(/^(\d{5})(\d{0,3})/, "$1-$2") : value;
});

document.getElementById("cpf").addEventListener("input", function (event) {
  let value = event.target.value.replace(/\D/g, "").slice(0, 11);
  if (value.length >= 10)
    event.target.value = value.replace(
      /(\d{3})(\d{3})(\d{3})(\d{0,2})/,
      "$1.$2.$3-$4"
    );
  else if (value.length >= 7)
    event.target.value = value.replace(/(\d{3})(\d{3})(\d{0,3})/, "$1.$2.$3");
  else if (value.length >= 4)
    event.target.value = value.replace(/(\d{3})(\d{0,3})/, "$1.$2");
  else event.target.value = value;
});

document.getElementById("telefone").addEventListener("input", function (event) {
  let value = event.target.value.replace(/\D/g, "").slice(0, 11);
  if (value.length >= 2 && value.length <= 6)
    event.target.value = value.replace(/^(\d{2})(\d{0,4})/, "($1) $2");
  else if (value.length > 6)
    event.target.value = value.replace(/^(\d{2})(\d{5})(\d{0,4})/, "($1) $2-$3");
  else event.target.value = value;
});

document.getElementById("estado").addEventListener("input", function (event) {
  event.target.value = event.target.value.replace(/[^a-zA-Z]/g, "").slice(0, 2).toUpperCase();
});

// API CEP
document.getElementById("cep").addEventListener("blur", async function () {
  const cepDigits = this.value.replace(/\D/g, "");
  if (!cepDigits) return;

  if (!isValidCEP(cepDigits)) {
    setFieldError("cep", "Informe um CEP válido (00000-000).");
    return;
  }

  try {
    const response = await fetch(`https://brasilapi.com.br/api/cep/v1/${cepDigits}`);
    if (!response.ok) {
      throw new Error("CEP não encontrado");
    }
    const data = await response.json();

    const mapaCampos = {
      estado: "state",
      cidade: "city",
      bairro: "neighborhood",
      endereco: "street",
    };

    ["estado", "cidade", "bairro", "endereco"].forEach((id) => {
      const input = document.getElementById(id);
      if (!input) return;
      input.value = data[mapaCampos[id]] || "";
      input.classList.add("readonly-style");
      setFieldError(id, null);
    });

    const estadoInput = document.getElementById("estado");
    if (estadoInput) estadoInput.value = estadoInput.value.toUpperCase();

    setFieldError("cep", null);
  } catch (error) {
    console.error("Erro da API de CEP:", error);
    setFieldError("cep", "Não foi possível localizar o CEP informado.");
  }
});

// Limpar campos no load
window.addEventListener("load", () => {
  fieldOrder.forEach((field) => {
    const input = document.getElementById(field);
    if (!input) return;
    input.value = "";
    input.classList.remove("readonly-style");
    input.classList.remove("is-invalid");
    input.removeAttribute("aria-invalid");

    const feedback = document.getElementById(`error-${field}`);
    if (feedback) {
      feedback.textContent = "";
      feedback.style.display = "none";
    }
  });
});

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

const inputDate = document.getElementById("data");
if (inputDate) {
  if (inputDate.showPicker) {
    inputDate.showPicker();
  } else {
    inputDate.focus();
  }
}

function calculateAge(birthDate) {
  const today = new Date();
  let age = today.getFullYear() - birthDate.getFullYear();
  const monthDiff = today.getMonth() - birthDate.getMonth();

  if (monthDiff < 0 || (monthDiff === 0 && today.getDate() < birthDate.getDate())) {
    age -= 1;
  }

  return age;
}}

function normalizeSpaces(inputValue) {
  let trimmedText = inputValue.trim();

  let wordsArray = trimmedText.split(" ");

  filteredWordsArray = wordsArray.filter((word) => word != "");

  normalizedText = filteredWordsArray.join(" ");
}


function getId(id) {
  return document.getElementById(`#${id}`);
}