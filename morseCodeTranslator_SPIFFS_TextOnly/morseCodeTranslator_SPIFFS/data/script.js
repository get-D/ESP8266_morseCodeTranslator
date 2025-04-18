
function handleSubmit(event) {
  event.preventDefault();
  const text = document.getElementById("textInput").value.trim();
  if (!text) {
    showModal("⚠️ Please enter a message.");
    return;
  }

  const controller = new AbortController();
  const timeoutId = setTimeout(() => controller.abort(), 7000);

  fetch(`/send?text=${encodeURIComponent(text)}`, {
    method: "GET",
    signal: controller.signal
  })
  .then(response => {
    clearTimeout(timeoutId);
    if (response.ok) {
      showModal("✅ Sent to buzzer!");
      document.getElementById("textInput").value = "";
    } else {
      showModal("❌ Failed to send to buzzer.");
    }
  })
  .catch(err => {
    if (err.name === "AbortError") {
      showModal("⏳ NodeMCU took too long to respond.");
    }
  });
}

function showModal(message) {
  const modal = document.getElementById("confirmationModal");
  const msg = document.getElementById("modalMessage");
  msg.innerHTML = message;
  modal.style.display = "flex";
}

function closeModal() {
  document.getElementById("confirmationModal").style.display = "none";
}
