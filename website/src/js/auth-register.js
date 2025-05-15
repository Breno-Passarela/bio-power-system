const form = {
  nome: "",
  sobrenome: "",
  email: "",
  senha: "",
  telefone: "",
  cpf: "",
  endereco: "",
  cep: "",
  data: ""  
};

document.getElementById("registerForm").addEventListener("submit", function (e) {
  e.preventDefault();

  // Preenche o objeto com os valores do formulário
  form.nome = document.getElementById("nome").value.trim();
  form.sobrenome = document.getElementById("sobrenome").value.trim();
  form.email = document.getElementById("email").value.trim();
  form.senha = document.getElementById("senha").value.trim();
  form.telefone = document.getElementById("telefone").value.trim();
  form.cpf = document.getElementById("cpf").value.trim();
  form.endereco = document.getElementById("endereco").value.trim();
  form.cep = document.getElementById("cep").value.trim();
  form.data = document.getElementById("data").value.trim();

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
  if (!form.sobrenome) newErrors.sobrenome = 'Sobrenome é obrigatório.';
  if (!emailRegex.test(form.email)) newErrors.email = 'E-mail inválido.';
  if (!strongPasswordRegex.test(form.senha)) newErrors.senha = 'A senha deve ter no mínimo 8 caracteres <br> letra maiúscula <br> minúscula <br> Número <br> caractere especial.';
  if (!/^\d{11}$/.test(form.telefone)) newErrors.telefone = 'Telefone inválido. Deve conter 11 dígitos.';
  if (!/^\d{11}$/.test(form.cpf)) newErrors.cpf = 'CPF inválido. Deve conter 11 dígitos.';
  if (!form.endereco) newErrors.endereco = 'Endereço é obrigatório.';
  if (!/^\d{8}$/.test(form.cep)) newErrors.cep = 'CEP inválido. Deve conter 8 dígitos.';
  if (!form.data) newErrors.data = 'Data é obrigatória';
  if (!form.genero) newErrors.genero = 'Gênero é obrigatório';

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

// Mostrar/ocultar senha
const togglePassword = document.getElementById("togglePassword");
const senhaInput = document.getElementById("senha");

togglePassword.addEventListener("click", () => {
  const isPassword = senhaInput.type === "password";
  senhaInput.type = isPassword ? "text" : "password";
  togglePassword.classList.toggle("fa-eye");
  togglePassword.classList.toggle("fa-eye-slash");
});
