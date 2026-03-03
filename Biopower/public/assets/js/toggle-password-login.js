function passwordShow(toggleId, inputId) {
  const toggleIcon = document.getElementById(toggleId);
  const input = document.getElementById(inputId);

  const isPassword = input.type === "password";
  input.type = isPassword ? "text" : "password";

  if (isPassword) {
    toggleIcon.classList.replace("fa-eye", "fa-eye-slash");
  } else {
    toggleIcon.classList.replace("fa-eye-slash", "fa-eye");
  }
}