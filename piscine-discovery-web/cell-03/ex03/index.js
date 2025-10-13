const ftListEl = document.querySelector('#ft_list');

/**
 * Initializes a new DOM element for a TODO
 * @param {number} i 
 * @param {string} text 
 * @returns DOM element
 */
const newTodoElement = (i, text) => {
  const element = document.createElement('div');
  element.id = `todo_${i}`;
  element.className = 'todo_element';
  element.innerText = text ?? 'INVALID';
  element.onclick = () => {delTodoElement(i)};
  return (element);
}

/**
 * Moves all element by one seat backward from the element index passed
 * @param {number} from 
 */
const moveAllBackwardFrom = (from) => {
  let amount = localStorage.length;
  // Move items backwards, starting from the removed index
  for (let i = from; i < amount - 1; i++) {
    const elementText = localStorage.getItem('todo_' + (i + 1));
    localStorage.setItem('todo_' + i, elementText);
  }
}

/**
 * Moves all element by one seat forward from the element index passed
 * @param {number} from 
 */
const moveAllForwardFrom = (from) => {
  let amount = localStorage.length;
  // Start from the last item and move backward
  for (let i = amount - 1; i >= from; i--) {
    const elementText = localStorage.getItem('todo_' + i);
    localStorage.setItem('todo_' + (i + 1), elementText);
  }
}

/**
 * Removes a TODO in the local storage
 * @param {number} idx 
 */
const removeOne = (idx) => {
  let amount = localStorage.length;
  moveAllBackwardFrom(idx);
  localStorage.removeItem('todo_' + (amount - 1));
}
const delTodoElement = (idx) => {
  removeOne(idx);
  updateDom();
}

/**
 * Updates the DOM to reflect changes to the local storage
 */
const updateDom = () => {
  // Remove all elements
  ftListEl.innerHTML = '';

  let amount = localStorage.length;
  for (let i = 0; i < amount; i++) {
    const elementText = localStorage.getItem('todo_' + i);
    const element = newTodoElement(i, elementText);
    ftListEl.appendChild(element);
  }
}

const addAtTop = (text) => {
  moveAllForwardFrom(0);
  localStorage.setItem('todo_0', text);
}

const askAndAdd = () => {
  let amount = localStorage.length;
  const elementText = window.prompt("Nom du TODO", 'Task ' + (amount + 1));
  addAtTop(elementText);
  updateDom();
}

const clearTodo = () => {
  localStorage.clear();
  updateDom();
}

const addTest = () => {
  clearTodo();
  addAtTop('“Be yourself; everyone else is already taken.” ― Oscar Wilde');
  addAtTop('“Two things are infinite: the universe and human stupidity; and I\'m not sure about the universe.” ― Albert Einstein');
  addAtTop('“You only live once, but if you do it right, once is enough.” ― Mae West');
  addAtTop('“In three words I can sum up everything I\'ve learned about life: it goes on.” ― Robert Frost');
  addAtTop('“If you tell the truth, you don\'t have to remember anything.” ― Mark Twain');
  addAtTop('“Always forgive your enemies; nothing annoys them so much.” ― Oscar Wilde');
  updateDom();
}

//////////////////////////////////////////////////////////////////////

updateDom();
