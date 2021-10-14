if (localStorage.getItem("memo")) {
  document.getElementById("memoField").value = localStorage.getItem("memo");
}

document.getElementById("memoField").addEventListener("change", (event) => {
  localStorage.setItem("memo", document.getElementById("memoField").value);
});

document.getElementById("saveMemo").addEventListener("click", (event) => {
  localStorage.removeItem("memo");
});

document.getElementById("copyMagicLink").addEventListener("click", (event) => {
  const token = document.getElementById("magicLink").value;
  const link = document.location.origin + "/magic?token=" + token;
  navigator.clipboard.writeText(link);
});
