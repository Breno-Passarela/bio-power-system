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
  bairro: ""
};

document.getElementById("registerForm").addEventListener("submit", function (e) {
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

  const strongPasswordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[\W_]).{8,}$/;
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

  if (!form.nome) newErrors.nome = 'Nome é obrigatório.';
  if (!emailRegex.test(form.email)) newErrors.email = 'E-mail inválido.';
  if (!strongPasswordRegex.test(form.senha)) newErrors.senha = 'A senha deve ter no mínimo 8 caracteres <br> letra maiúscula <br> minúscula <br> Número <br> caractere especial.';
  if (!/^\d{11}$/.test(form.telefone)) newErrors.telefone = 'Telefone inválido. Deve conter 11 dígitos.';
  if (!/^\d{11}$/.test(form.cpf)) newErrors.cpf = 'CPF inválido. Deve conter 11 dígitos.';
  if (!form.endereco) newErrors.endereco = 'Endereço é obrigatório.';
  if (!form.numero) newErrors.numero = 'Número é obrigatório.';
  if (!/^\d{8}$/.test(form.cep)) newErrors.cep = 'CEP inválido. Deve conter 8 dígitos.';
  if (!form.data) newErrors.data = 'Data é obrigatória';
  if (!form.genero || form.genero == "not_valid") newErrors.genero = 'Gênero é obrigatório';
  if (!form.cidade) newErrors.cidade = 'Cidade é obrigatória.';
  if (!form.estado) newErrors.estado = 'Estado é obrigatório.';
  if (!form.bairro) newErrors.bairro = 'Bairro é obrigatório.';

  return newErrors;
};

function showErrors(errors) {
  for (const field in errors) {
    const errorSpan = document.getElementById(`error-${field}`);
    if (errorSpan) {
      errorSpan.innerHTML = errors[field];
    }
  }
}


function clearErrors() {
  const errorSpans = document.querySelectorAll(".error-message");
  errorSpans.forEach(span => span.textContent = "");
}

// Api de CEP
document.getElementById("cep").addEventListener("blur", async function () {
  const cep = this.value.replace(/\D/g, "");

  if (cep.length !== 8) {
    console.warn("CEP inválido.");
    return;
  }

  try {
    const response = await fetch(`https://brasilapi.com.br/api/cep/v1/${cep}`);
    if (!response.ok) throw new Error("CEP não encontrado");

    const data = await response.json();

    const fields = {
      estado: data.state,
      cidade: data.city,
      bairro: data.neighborhood,
      endereco: data.street,
    };

    for (const id in fields) {
      const input = document.getElementById(id);
      input.value = fields[id] || "";
      input.classList.add("readonly-style");
    }

  } catch (error) {
    console.error("Erro ao buscar o CEP:", error);
  }
});

// Limpa as informações da página ao carregar
window.addEventListener("load", () => {
  const camposParaLimpar = [
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
    "numero"
  ];
  
  camposParaLimpar.forEach((id) => {
    const input = document.getElementById(id);
    if (input) {
      input.value = "";
      input.classList.remove("readonly-style");
    }
  });
});

// Máscaras

// Máscara de CEP
document.getElementById("cep").addEventListener("input", function () {
  let value = this.value.replace(/\D/g, "").slice(0, 8);
  if (value.length > 5) {
    this.value = value.replace(/^(\d{5})(\d{0,3})/, "$1-$2");
  } else {
    this.value = value;
  }
});

// Máscara de CPF

document.getElementById("cpf").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, ""); // Remove tudo que não é número
  value = value.slice(0, 11); // Limita a 11 dígitos

  if (value.length >= 10) {
    e.target.value = value.replace(/(\d{3})(\d{3})(\d{3})(\d{0,2})/, "$1.$2.$3-$4");
  } else if (value.length >= 7) {
    e.target.value = value.replace(/(\d{3})(\d{3})(\d{0,3})/, "$1.$2.$3");
  } else if (value.length >= 4) {
    e.target.value = value.replace(/(\d{3})(\d{0,3})/, "$1.$2");
  } else {
    e.target.value = value;
  }
});

// Máscara de Celular

document.getElementById("telefone").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, "");
  value = value.slice(0, 11);

  if (value.length >= 2 && value.length <= 6) {
    e.target.value = value.replace(/^(\d{2})(\d{0,4})/, "($1) $2");
  } else if (value.length > 6) {
    e.target.value = value.replace(/^(\d{2})(\d{5})(\d{0,4})/, "($1) $2-$3");
  } else {
    e.target.value = value;
  }
});

// Máscara de data

document.getElementById("data").addEventListener("input", function (e) {
  let value = e.target.value.replace(/\D/g, "").slice(0, 8);

  if (value.length >= 5) {
    e.target.value = value.replace(/(\d{2})(\d{2})(\d{0,4})/, "$1/$2/$3");
  } else if (value.length >= 3) {
    e.target.value = value.replace(/(\d{2})(\d{0,2})/, "$1/$2");
  } else {
    e.target.value = value;
  }
});