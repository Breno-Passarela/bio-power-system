var dados = [
  {
    id: 1,
    name: "Creatina",
    descricao: "descricao muito massa sobre a Creatina",
    price: 10.0,
    quantidade: 2,
  },
  {
    id: 2,
    name: "Whey de Chocolate",
    descricao: "descricao muito massa sobre o whey",
    price: 15.5,
    quantidade: 5,
  },
  {
    id: 3,
    name: "Cafeina",
    descricao: "Descrição muito massa sobre a cafeina",
    price: 7.25,
    quantidade: 10,
  },
];

function montarTabela() {
  let vTbody = document.querySelector("#grid tbody");
  if (!vTbody) return;
  let html = "";
  for (let item of dados) {
    html += `
        <tr>
            <td class="text-center coluna">
              <input type="checkbox" class="check-row" data-id="${item.id}">
            </td>
            <td class="coluna text-center">${item.id}</td>
            <td class="coluna">${item.name}</td>
            <td class="coluna">${item.descricao}</td>
            <td class="coluna text-center">R$ ${item.price.toFixed(2)}</td>
            <td class="coluna text-center">${item.quantidade}</td>
            <td class="text-center coluna">
              <a class="btn btn-sm btn-danger btn-remover-linha" onclick="excluirItem(${item.id})">
                <i class="fa fa-trash"></i>
              </a>
            </td>
        </tr>
    `;
  }
  vTbody.innerHTML = html;
}

function marcarInvalid(input, mensagem) {
  if (!input) return;
  input.classList.add("is-invalid");
  const feedback = input.closest(".form-floating")?.querySelector(".invalid-feedback");
  if (feedback) {
    feedback.textContent = mensagem;
  }
}

function limparValidacao(inputs) {
  inputs.forEach((input) => {
    if (!input) return;
    input.classList.remove("is-invalid");
    const feedback = input.closest(".form-floating")?.querySelector(".invalid-feedback");
    if (feedback) {
      feedback.textContent = "";
    }
  });
}

function adicionarItem() {
  let nomeInput = document.querySelector("#nome-produtos");
  let descricaoInput = document.querySelector("#descricao-produtos");
  let precoInput = document.querySelector("#preco-produtos");
  let quantidadeInput = document.querySelector("#quantidade-produtos");

  if (!nomeInput || !descricaoInput || !precoInput || !quantidadeInput) return;

  limparValidacao([nomeInput, descricaoInput, precoInput, quantidadeInput]);

  let valido = true;

  if (nomeInput.value.trim() === "") {
    marcarInvalid(nomeInput, "O nome é obrigatório.");
    valido = false;
  }

  if (descricaoInput.value.trim() === "") {
    marcarInvalid(descricaoInput, "A descrição é obrigatória.");
    valido = false;
  }

  const precoConvertido = parseFloat(precoInput.value);
  if (precoInput.value.trim() === "" || Number.isNaN(precoConvertido)) {
    marcarInvalid(precoInput, "Informe um preço válido.");
    valido = false;
  }

  const quantidadeConvertida = parseInt(quantidadeInput.value, 10);
  if (quantidadeInput.value.trim() === "" || Number.isNaN(quantidadeConvertida)) {
    marcarInvalid(quantidadeInput, "Informe uma quantidade válida.");
    valido = false;
  }

  if (!valido) {
    return;
  }

  let novoItem = {
    id: dados.length > 0 ? dados[dados.length - 1].id + 1 : 1,
    name: nomeInput.value.trim(),
    descricao: descricaoInput.value.trim(),
    price: precoConvertido,
    quantidade: quantidadeConvertida,
  };
  dados.push(novoItem);
  montarTabela();
  nomeInput.value = "";
  descricaoInput.value = "";
  precoInput.value = "";
  quantidadeInput.value = "";
  nomeInput.focus();
}

function excluirItem(id) {
  let listaAux = [];
  for (let i = 0; i < dados.length; i++) {
    if (dados[i].id != id) {
      listaAux.push(dados[i]);
    }
  }
  dados = listaAux;
  montarTabela();
}

function excluirSelecionados() {
  let listaCk = document.querySelectorAll(".check-row");
  if (listaCk.length > 0) {
    for (let ck of listaCk) {
      if (ck.checked == true) {
        excluirItem(parseInt(ck.dataset.id, 10));
      }
    }
  } else {
    alert("Não há produtos na lista para serem excluídos.");
  }
}

function selecionaTodos() {
  let listaCk = document.querySelectorAll(".check-row");
  let ckpai = document.querySelector("#ckTodos");
  if (!ckpai) return;
  for (let ck of listaCk) {
    ck.checked = ckpai.checked;
  }
}

document.addEventListener(
  "DOMContentLoaded",
  function () {
    montarTabela();

    var button = document.querySelector("#btn-add");
    if (button) {
      button.addEventListener("click", adicionarItem, false);
    }

    var buttonExcluirSelecionado = document.querySelector("#btnExcluirSelecionados");
    if (buttonExcluirSelecionado) {
      buttonExcluirSelecionado.addEventListener("click", excluirSelecionados, false);
    }

    var ckpai = document.querySelector("#ckTodos");
    if (ckpai) {
      ckpai.addEventListener("click", selecionaTodos, false);
    }
  },
  false
);
