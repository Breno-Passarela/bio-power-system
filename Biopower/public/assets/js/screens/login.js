// src/js/auth/auth-login.js
document.addEventListener("DOMContentLoaded", () => {
  const loginForm = document.querySelector(".login-form");
  const emailInput = document.getElementById("email");
  const passwordInput = document.getElementById("password");

  const showAlert = (options) => {
    if (window.Swal) return window.Swal.fire(options);
    console.log(options.title || options.text || "");
    return Promise.resolve();
  };

  loginForm.addEventListener("submit", (e) => {
    e.preventDefault();

    const email = emailInput.value.trim();
    const password = passwordInput.value.trim();

    if (!email || !password) {
      showAlert({ icon: "warning", title: "Por favor, preencha todos os campos." });
      return;
    }

    if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
      showAlert({ icon: "warning", title: "Por favor, insira um e-mail válido." });
      return;
    }

    const newToken = generateToken();
    localStorage.setItem("token", newToken);

    console.log("Token set in localStorage:", localStorage.getItem("token"));

    window.location.href = "../../home.html";
  });
});
