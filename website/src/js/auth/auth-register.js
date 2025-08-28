const form = {
  nome: "",
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
};

document
  .getElementById("registerForm")
  .addEventListener("submit", function (e) {
    e.preventDefault();

    form.nome = document.getElementById("nome").value.trim();
    form.email = document.getElementById("email").value.trim();
    form.senha = document.getElementById("senha").value.trim();
    form.telefone = document.getElementById("telefone").value.trim();
    form.cpf = document.getElementById("cpf").value.trim();
    form.endereco = document.getElementById("endereco").value.trim();
    form.numero = document.getElementById("numero").value.trim();
    form.cep = document.getElementById("cep").value.trim();
    form.data = document.getElementById("data").value.trim();
    form.genero = document.getElementById("genero").value;
    form.estado = document.getElementById("estado").value.trim();
    form.cidade = document.getElementById("cidade").value.trim();
    form.bairro = document.getElementById("bairro").value.trim();

    const errors = validateFields();
    clearErrors();

    if (Object.keys(errors).length > 0) {
      showErrors(errors);
    } else {
      this.submit();
    }
  });

const validateFields = () => {
  const newErrors = {};
  const strongPasswordRegex =
    /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

  const rawCPF = form.cpf.replace(/\D/g, "");
  const rawTelefone = form.telefone.replace(/\D/g, "");
  const rawCEP = form.cep.replace(/\D/g, "");

  if (!form.nome) newErrors.nome = "Nome é obrigatório.";
  if (!emailRegex.test(form.email)) newErrors.email = "E-mail inválido.";
  if (!strongPasswordRegex.test(form.senha))
    newErrors.senha =
      "Senha deve ter 8 caracteres, maiúscula, minúscula, número e símbolo.";
  if (!/^\d{11}$/.test(rawTelefone))
    newErrors.telefone = "Telefone inválido. Deve conter 11 dígitos.";
  if (!/^\d{11}$/.test(rawCPF))
    newErrors.cpf = "CPF inválido. Deve conter 11 dígitos.";
  if (!form.endereco) newErrors.endereco = "Endereço é obrigatório.";
  if (!form.numero) newErrors.numero = "Número é obrigatório.";
  if (!/^\d{8}$/.test(rawCEP))
    newErrors.cep = "CEP inválido. Deve conter 8 dígitos.";
  if (!form.data) newErrors.data = "Data é obrigatória";
  if (!form.genero || form.genero == "not_valid")
    newErrors.genero = "Gênero é obrigatório";
  if (!form.cidade) newErrors.cidade = "Cidade é obrigatória.";
  if (!form.estado) newErrors.estado = "Estado é obrigatório.";
  if (!form.bairro) newErrors.bairro = "Bairro é obrigatório.";

  return newErrors;
};

function showErrors(errors) {
  for (const field in errors) {
    const errorSpan = document.getElementById(`error-${field}`);
    if (errorSpan) errorSpan.innerHTML = errors[field];
  }
}

function clearErrors() {
  document
    .querySelectorAll(".error-message")
    .forEach((span) => (span.textContent = ""));
}

// Máscaras
document.getElementById("cep").addEventListener("input", function () {
  let value = this.value.replace(/\D/g, "").slice(0, 8);
  this.value =
    value.length > 5 ? value.replace(/^(\d{5})(\d{0,3})/, "$1-$2") : value;
});

document.getElementById("cpf").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, "").slice(0, 11);
  if (value.length >= 10)
    e.target.value = value.replace(
      /(\d{3})(\d{3})(\d{3})(\d{0,2})/,
      "$1.$2.$3-$4"
    );
  else if (value.length >= 7)
    e.target.value = value.replace(/(\d{3})(\d{3})(\d{0,3})/, "$1.$2.$3");
  else if (value.length >= 4)
    e.target.value = value.replace(/(\d{3})(\d{0,3})/, "$1.$2");
  else e.target.value = value;
});

document.getElementById("telefone").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, "").slice(0, 11);
  if (value.length >= 2 && value.length <= 6)
    e.target.value = value.replace(/^(\d{2})(\d{0,4})/, "($1) $2");
  else if (value.length > 6)
    e.target.value = value.replace(/^(\d{2})(\d{5})(\d{0,4})/, "($1) $2-$3");
  else e.target.value = value;
});

document.getElementById("data").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, "").slice(0, 8);
  if (value.length >= 5)
    e.target.value = value.replace(/(\d{2})(\d{2})(\d{0,4})/, "$1/$2/$3");
  else if (value.length >= 3)
    e.target.value = value.replace(/(\d{2})(\d{0,2})/, "$1/$2");
  else e.target.value = value;
});

// API CEP
document.getElementById("cep").addEventListener("blur", async function () {
  const cep = this.value.replace(/\D/g, "");
  if (cep.length !== 8) return;
  try {
    const res = await fetch(`https://brasilapi.com.br/api/cep/v1/${cep}`);
    if (!res.ok) throw new Error("CEP não encontrado");
    const data = await res.json();
    ["estado", "cidade", "bairro", "endereco"].forEach((id) => {
      const input = document.getElementById(id);
      input.value =
        data[
          id === "estado"
            ? "state"
            : id === "cidade"
            ? "city"
            : id === "bairro"
            ? "neighborhood"
            : "street"
        ] || "";
      input.classList.add("readonly-style");
    });
  } catch (e) {
    console.error("Erro CEP:", e);
  }
});

// Limpar campos no load
window.addEventListener("load", () => {
  [
    "nome",
    "email",
    "senha",
    "telefone",
    "cpf",
    "cep",
    "data",
    "genero",
    "estado",
    "cidade",
    "bairro",
    "endereco",
    "numero",
  ].forEach((id) => {
    const input = document.getElementById(id);
    if (input) {
      input.value = "";
      input.classList.remove("readonly-style");
    }
  });
});

// Botões do form tipo button
document.querySelectorAll("button").forEach((btn) => {
  if (!btn.type) btn.type = "button";
});

// Função para mostrar senha
function passwordShow(toggleId, inputId) {
  const toggle = document.getElementById(toggleId);
  const input = document.getElementById(inputId);
  if (input.type === "password") {
    input.type = "text";
    toggle.classList.replace("fa-eye", "fa-eye-slash");
  } else {
    input.type = "password";
    toggle.classList.replace("fa-eye-slash", "fa-eye");
  }
}
