var dados = [
  {
    id: 1,
    nome: "Creatina Monohidratada",
    descricao: "Creatina 100% pura para força, explosão e desempenho nos treinos.",
    categoria: "Suplementos",
    sku: "CR-0001",
    fornecedor: "Bio Power Labs",
    preco: 129.9,
    quantidade: 20,
    unidade: "g",
    peso: 300,
    validade: "2026-06-30",
    status: "Disponível",
    imagem: "https://www.dotcom-monitor.com/blog/wp-content/uploads/sites/3/2019/09/404-error.jpg",
  },
  {
    id: 2,
    nome: "Whey Protein Chocolate",
    descricao: "Whey protein sabor chocolate com alta concentração proteica.",
    categoria: "Suplementos",
    sku: "WP-CHOC-450",
    fornecedor: "Protein Foods",
    preco: 189.5,
    quantidade: 15,
    unidade: "g",
    peso: 450,
    validade: "2025-09-15",
    status: "Disponível",
    imagem: "https://www.dotcom-monitor.com/blog/wp-content/uploads/sites/3/2019/09/404-error.jpg",
  },
  {
    id: 3,
    nome: "Cafeína 210mg",
    descricao: "Cafeína encapsulada para foco, disposição e energia diária.",
    categoria: "Vitaminas",
    sku: "CAF-210",
    fornecedor: "Bio Power Labs",
    preco: 59.9,
    quantidade: 40,
    unidade: "Caps",
    peso: 120,
    validade: "2025-04-01",
    status: "Disponível",
    imagem: "https://www.dotcom-monitor.com/blog/wp-content/uploads/sites/3/2019/09/404-error.jpg",
  },
  {
    id: 4,
    nome: "Pré-Workout Explosive",
    descricao: "Pré-treino com blend de estimulantes para força e resistência.",
    categoria: "Suplementos",
    sku: "PW-EXP-300",
    fornecedor: "Max Performance",
    preco: 149.0,
    quantidade: 10,
    unidade: "g",
    peso: 300,
    validade: "2024-12-20",
    status: "Em breve",
    imagem: "https://www.dotcom-monitor.com/blog/wp-content/uploads/sites/3/2019/09/404-error.jpg",
  },
  {
    id: 5,
    nome: "Ômega 3 Concentrado",
    descricao: "Cápsulas com alta concentração de EPA e DHA para saúde cardiovascular.",
    categoria: "Vitaminas",
    sku: "OMG-120",
    fornecedor: "Saúde Viva",
    preco: 89.75,
    quantidade: 25,
    unidade: "Caps",
    peso: 180,
    validade: "2026-02-10",
    status: "Disponível",
    imagem: "https://www.dotcom-monitor.com/blog/wp-content/uploads/sites/3/2019/09/404-error.jpg",
  },
];

const productForm = {
  nome: "",
  descricao: "",
  categoria: "",
  sku: "",
  fornecedor: "",
  preco: "",
  quantidade: "",
  unidade: "",
  peso: "",
  validade: "",
  status: "",
  imagem: "",
};

const fieldOrder = [
  "nome-produtos",
  "descricao-produtos",
  "categoria-produto",
  "sku-produto",
  "fornecedor-produto",
  "preco-produtos",
  "quantidade-produtos",
  "unidade-produto",
  "peso-produto",
  "validade-produto",
  "status-produto",
  "imagem-produto",
];

const PRODUCT_NAME_MIN_LENGTH = 3;
const DESCRIPTION_MIN_LENGTH = 10;
const PRODUCT_NAME_REGEX = /^[A-Za-zÀ-ÿ0-9&.,:'\-()]+(?: [A-Za-zÀ-ÿ0-9&.,:'\-()]+)*$/;
const SUPPLIER_REGEX = /^[A-Za-zÀ-ÿ0-9&.,'()\-]{3,}(?: [A-Za-zÀ-ÿ0-9&.,'()\-]{2,})*$/;
const SKU_REGEX = /^[A-Z0-9][A-Z0-9._-]{2,19}$/;

function buildErrorList(errors) {
  const ul = document.createElement("ul");
  ul.classList.add("mb-0", "ps-3");
  errors.forEach((err) => {
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

  if (message && message.length > 0) {
    element.classList.add("is-invalid");
    const messages = Array.isArray(message) ? message : [message];
    const ul = buildErrorList(messages);
    feedback.appendChild(ul);
    feedback.style.display = "flex";
  } else {
    element.classList.remove("is-invalid");
    feedback.style.display = "none";
  }
}

function clearErrors() {
  fieldOrder.forEach((fieldId) => setFieldError(fieldId, null));
}

function normalizeSpaces(str) {
  return (str || "").trim().split(" ").filter(Boolean).join(" ");
}

function collectFormValues() {
  productForm.nome = normalizeSpaces(document.getElementById("nome-produtos")?.value || "");
  productForm.descricao = normalizeSpaces(document.getElementById("descricao-produtos")?.value || "");
  productForm.categoria = document.getElementById("categoria-produto")?.value || "";
  productForm.sku = (document.getElementById("sku-produto")?.value || "").trim().toUpperCase();
  productForm.fornecedor = normalizeSpaces(document.getElementById("fornecedor-produto")?.value || "");
  productForm.preco = (document.getElementById("preco-produtos")?.value || "").trim();
  productForm.quantidade = (document.getElementById("quantidade-produtos")?.value || "").trim();
  productForm.unidade = document.getElementById("unidade-produto")?.value || "";
  productForm.peso = (document.getElementById("peso-produto")?.value || "").trim();
  productForm.validade = document.getElementById("validade-produto")?.value || "";
  productForm.status = document.getElementById("status-produto")?.value || "";
  productForm.imagem = (document.getElementById("imagem-produto")?.value || "").trim();
}

function validateFields() {
  const errors = {};

  // Nome
  errors["nome-produtos"] = [];
  if (!productForm.nome) {
    errors["nome-produtos"].push("Informe o nome do produto.");
  } else {
    if (productForm.nome.length < PRODUCT_NAME_MIN_LENGTH) {
      errors["nome-produtos"].push(`Nome deve ter pelo menos ${PRODUCT_NAME_MIN_LENGTH} caracteres.`);
    }
    if (!PRODUCT_NAME_REGEX.test(productForm.nome)) {
      errors["nome-produtos"].push("Nome contém caracteres inválidos.");
    }
  }
  if (errors["nome-produtos"].length === 0) delete errors["nome-produtos"];

  // Descrição
  errors["descricao-produtos"] = [];
  if (!productForm.descricao) {
    errors["descricao-produtos"].push("Informe a descrição.");
  } else if (productForm.descricao.length < DESCRIPTION_MIN_LENGTH) {
    errors["descricao-produtos"].push(`Descrição deve ter pelo menos ${DESCRIPTION_MIN_LENGTH} caracteres.`);
  }
  if (errors["descricao-produtos"].length === 0) delete errors["descricao-produtos"];

  // Categoria
  if (!productForm.categoria) {
    errors["categoria-produto"] = ["Selecione a categoria."];
  }

  // SKU
  errors["sku-produto"] = [];
  if (!productForm.sku) {
    errors["sku-produto"].push("Informe o SKU.");
  } else if (!SKU_REGEX.test(productForm.sku)) {
    errors["sku-produto"].push("SKU deve ter 3 a 20 caracteres (letras, números, ponto, traço ou underscore).");
  } else if (dados.some((item) => item.sku.toUpperCase() === productForm.sku)) {
    errors["sku-produto"].push("SKU já cadastrado.");
  }
  if (errors["sku-produto"]?.length === 0) delete errors["sku-produto"];

  // Fornecedor
  errors["fornecedor-produto"] = [];
  if (!productForm.fornecedor) {
    errors["fornecedor-produto"].push("Informe o fornecedor.");
  } else if (!SUPPLIER_REGEX.test(productForm.fornecedor)) {
    errors["fornecedor-produto"].push("Fornecedor contém caracteres inválidos.");
  }
  if (errors["fornecedor-produto"].length === 0) delete errors["fornecedor-produto"];

  // Preço
  const precoValor = parseLocaleNumber(productForm.preco);
  errors["preco-produtos"] = [];
  if (!productForm.preco) {
    errors["preco-produtos"].push("Informe o preço.");
  } else if (!Number.isFinite(precoValor) || precoValor <= 0) {
    errors["preco-produtos"].push("Preço deve ser um valor numérico maior que zero.");
  }
  if (errors["preco-produtos"].length === 0) delete errors["preco-produtos"];

  // Quantidade
  const quantidadeValor = Number.parseInt(productForm.quantidade, 10);
  errors["quantidade-produtos"] = [];
  if (productForm.quantidade === "") {
    errors["quantidade-produtos"].push("Informe a quantidade.");
  } else if (!Number.isInteger(quantidadeValor) || quantidadeValor < 0) {
    errors["quantidade-produtos"].push("Quantidade deve ser um número inteiro maior ou igual a zero.");
  }
  if (errors["quantidade-produtos"].length === 0) delete errors["quantidade-produtos"];

  // Unidade
  if (!productForm.unidade) {
    errors["unidade-produto"] = ["Selecione a unidade."];
  }

  // Peso / Volume
  const pesoValor = parseLocaleNumber(productForm.peso);
  errors["peso-produto"] = [];
  if (productForm.peso === "") {
    errors["peso-produto"].push("Informe o peso ou volume.");
  } else if (!Number.isFinite(pesoValor) || pesoValor <= 0) {
    errors["peso-produto"].push("Peso/volume deve ser um número maior que zero.");
  }
  if (errors["peso-produto"].length === 0) delete errors["peso-produto"];

  // Validade
  errors["validade-produto"] = [];
  if (productForm.validade) {
    const validadeDate = new Date(`${productForm.validade}T00:00:00`);
    const today = new Date();
    today.setHours(0, 0, 0, 0);
    if (Number.isNaN(validadeDate.getTime())) {
      errors["validade-produto"].push("Data de validade inválida.");
    } else if (validadeDate < today) {
      errors["validade-produto"].push("Data de validade não pode estar no passado.");
    }
  }
  if (errors["validade-produto"].length === 0) delete errors["validade-produto"];

  // Status
  if (!productForm.status) {
    errors["status-produto"] = ["Selecione o status."];
  }

  // Imagem
  errors["imagem-produto"] = [];
  if (productForm.imagem) {
    try {
      const url = new URL(productForm.imagem);
      if (!["http:", "https:"].includes(url.protocol)) {
        throw new Error();
      }
    } catch (e) {
      errors["imagem-produto"].push("Informe uma URL de imagem válida (http/https).");
    }
  }
  if (errors["imagem-produto"].length === 0) delete errors["imagem-produto"];

  return errors;
}

function formatCurrency(value) {
  const number = Number(value);
  if (!Number.isFinite(number)) return "R$ 0,00";
  return number.toLocaleString("pt-BR", { style: "currency", currency: "BRL" });
}

function formatWeight(value) {
  if (value === null || value === undefined || value === "") return "—";
  const number = Number(value);
  if (!Number.isFinite(number)) return "—";
  return number.toLocaleString("pt-BR", { minimumFractionDigits: 0, maximumFractionDigits: 3 });
}

function formatDate(value) {
  if (!value) return "—";
  const date = new Date(`${value}T00:00:00`);
  if (Number.isNaN(date.getTime())) return "—";
  return date.toLocaleDateString("pt-BR");
}

function montarTabela() {
  const tbody = document.querySelector("#grid tbody");
  if (!tbody) return;

  const linhas = dados
    .map((item) => {
      const imagemLink = item.imagem
        ? `<a href="${item.imagem}" target="_blank" rel="noopener noreferrer">Abrir</a>`
        : "—";

      return `
        <tr>
          <td class="text-center coluna">
            <input type="checkbox" class="check-row" data-id="${item.id}">
          </td>
          <td class="coluna text-center">${item.id}</td>
          <td class="coluna">${item.nome}</td>
          <td class="coluna-descricao">${item.descricao}</td>
          <td class="coluna">${item.categoria}</td>
          <td class="coluna text-center">${item.sku}</td>
          <td class="coluna">${item.fornecedor}</td>
          <td class="coluna text-center">${formatCurrency(item.preco)}</td>
          <td class="coluna text-center">${item.quantidade}</td>
          <td class="coluna text-center">${item.unidade}</td>
          <td class="coluna text-center">${formatWeight(item.peso)}</td>
          <td class="coluna text-center">${formatDate(item.validade)}</td>
          <td class="coluna text-center">${item.status}</td>
          <td class="coluna text-center">${imagemLink}</td>
          <td class="text-center coluna">
            <a class="btn btn-sm btn-danger btn-remover-linha" onclick="excluirItem(${item.id})">
              <i class="fa fa-trash"></i>
            </a>
          </td>
        </tr>
      `;
    })
    .join("");

  tbody.innerHTML = linhas;
}

function resetFormFields() {
  fieldOrder.forEach((fieldId) => {
    const input = document.getElementById(fieldId);
    if (!input) return;

    if (input.tagName === "SELECT") {
      input.selectedIndex = 0;
    } else {
      input.value = "";
    }
    input.classList.remove("is-invalid");
  });

  Object.keys(productForm).forEach((key) => {
    productForm[key] = "";
  });

  clearErrors();
  const ckTodos = document.getElementById("ckTodos");
  if (ckTodos) ckTodos.checked = false;
}

function adicionarItem(event) {
  if (event) event.preventDefault();

  clearErrors();
  collectFormValues();

  const errors = validateFields();
  Object.keys(errors).forEach((fieldId) => setFieldError(fieldId, errors[fieldId]));

  if (Object.keys(errors).length > 0) {
    return;
  }

  const precoValor = parseLocaleNumber(productForm.preco);
  const quantidadeValor = Number.parseInt(productForm.quantidade, 10);
  const pesoValor = parseLocaleNumber(productForm.peso);

  const novoId = dados.length > 0 ? Math.max(...dados.map((item) => item.id)) + 1 : 1;

  const novoItem = {
    id: novoId,
    nome: productForm.nome,
    descricao: productForm.descricao,
    categoria: productForm.categoria,
    sku: productForm.sku,
    fornecedor: productForm.fornecedor,
    preco: precoValor,
    quantidade: quantidadeValor,
    unidade: productForm.unidade,
    peso: pesoValor,
    validade: productForm.validade || "",
    status: productForm.status,
    imagem: productForm.imagem,
  };

  dados.push(novoItem);
  montarTabela();
  resetFormFields();

  const primeiroCampo = document.getElementById(fieldOrder[0]);
  primeiroCampo?.focus();
}

function excluirItem(id) {
  dados = dados.filter((item) => item.id !== id);
  montarTabela();
  const ckTodos = document.getElementById("ckTodos");
  if (ckTodos) ckTodos.checked = false;
}

function excluirSelecionados() {
  const listaCk = document.querySelectorAll(".check-row");
  if (listaCk.length === 0) {
    alert("Não há produtos na lista para serem excluídos.");
    return;
  }

  let alterou = false;
  listaCk.forEach((ck) => {
    if (ck.checked) {
      excluirItem(parseInt(ck.dataset.id, 10));
      alterou = true;
    }
  });

  if (!alterou) {
    alert("Selecione pelo menos um produto para excluir.");
  }
}

function selecionaTodos() {
  const listaCk = document.querySelectorAll(".check-row");
  const ckpai = document.querySelector("#ckTodos");
  if (!ckpai) return;
  listaCk.forEach((ck) => {
    ck.checked = ckpai.checked;
  });
}

document.addEventListener(
  "DOMContentLoaded",
  () => {
    applyMasks();
    montarTabela();
    resetFormFields();

    const button = document.querySelector("#btn-add");
    if (button) {
      button.addEventListener("click", adicionarItem, false);
    }

    const buttonExcluirSelecionado = document.querySelector("#btnExcluirSelecionados");
    if (buttonExcluirSelecionado) {
      buttonExcluirSelecionado.addEventListener("click", excluirSelecionados, false);
    }

    const ckpai = document.querySelector("#ckTodos");
    if (ckpai) {
      ckpai.addEventListener("click", selecionaTodos, false);
    }

    const formElement = document.getElementById("lista");
    if (formElement) {
      formElement.addEventListener("submit", (event) => {
        event.preventDefault();
        adicionarItem(event);
      });
    }
  },
  false
);

function parseLocaleNumber(value) {
  if (typeof value !== "string" || value.trim() === "") return NaN;
  const normalized = value.replace(/\./g, "").replace(",", ".");
  const number = Number(normalized);
  return Number.isFinite(number) ? number : NaN;
}

function applyMasks() {
  const skuInput = document.getElementById("sku-produto");
  if (skuInput) {
    skuInput.addEventListener("input", (event) => {
      event.target.value = event.target.value.replace(/[^A-Za-z0-9._-]/g, "").toUpperCase();
    });
  }

  const precoInput = document.getElementById("preco-produtos");
  if (precoInput) {
    precoInput.addEventListener("input", (event) => {
      const digits = event.target.value.replace(/\D/g, "");
      if (!digits) {
        event.target.value = "";
        return;
      }
      const number = Number(digits) / 100;
      event.target.value = number.toLocaleString("pt-BR", {
        minimumFractionDigits: 2,
        maximumFractionDigits: 2,
      });
    });
  }

  const quantidadeInput = document.getElementById("quantidade-produtos");
  if (quantidadeInput) {
    quantidadeInput.addEventListener("input", (event) => {
      event.target.value = event.target.value.replace(/\D/g, "");
    });
  }

  const pesoInput = document.getElementById("peso-produto");
  if (pesoInput) {
    pesoInput.addEventListener("input", (event) => {
      let value = event.target.value.replace(/[^\d,]/g, "");
      const parts = value.split(",");
      if (parts.length > 2) value = parts[0] + "," + parts.slice(1).join("");
      if (parts[1]?.length > 3) value = parts[0] + "," + parts[1].slice(0, 3);
      event.target.value = value;
    });
  }
}
