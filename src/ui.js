let source_button = document.getElementById("source_code_link");

source_button.addEventListener('click', function(){
  ipc.send('go_to_source');
}); 