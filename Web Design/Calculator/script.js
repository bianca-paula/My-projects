class Calculator{
    constructor(previousOperandElem,currentOperandElem){
        this.previousOperandElem=previousOperandElem
        this.currentOperandElem=currentOperandElem
        this.clear()
    }

    clear(){
        this.currentOperand=''
        this.previousOperand=''
        this.operation=undefined
    }

    delete(){
        this.currentOperand=this.currentOperand.toString().slice(0, -1)
    }

    power_of_two(){
      this.currentOperand=(this.currentOperand*this.currentOperand).toString()
    }

    appendNumber(number){
        if (number === '.' && this.currentOperand.includes('.')) return
        this.currentOperand = this.currentOperand.toString() + number.toString()
    }

    chooseOperation(operation){
    if (this.currentOperand === '') return
    if (this.previousOperand !== '') {
      this.compute()
    }
    this.operation = operation
    this.previousOperand = this.currentOperand
    this.currentOperand = ''
    }

    compute(){
        let computation
        const prev = parseFloat(this.previousOperand) 
        const current = parseFloat(this.currentOperand)
        if (isNaN(prev) || isNaN(current)) return
        switch (this.operation) {
          case '+':
            computation = prev + current
            break
          case '-':
            computation = prev - current
            break
          case '*':
            computation = prev * current
            break
          case '/':
            computation = prev / current
            break
          default:
            return
        }
        this.currentOperand = computation
        this.operation = undefined
        this.previousOperand = ''
        
    }

    getDisplayNumber(number){
        const stringNumber = number.toString()
        const integerDigits = parseFloat(stringNumber.split('.')[0])
        const decimalDigits = stringNumber.split('.')[1]

        let integerDisplay
        if (isNaN(integerDigits)){
            integerDisplay=''
        } else {
            integerDisplay = integerDigits.toLocaleString('en', 
            { maximumFractionDigits: 0 })
        }
        if (decimalDigits != null) {
            return `${integerDisplay}.${decimalDigits}`
          } else {
            return integerDisplay
          }
    }

    updateOperation(){
        this.currentOperandElem.innerText = this.getDisplayNumber(this.currentOperand)
      if (this.operation != null) {
        this.previousOperandElem.innerText =`${this.getDisplayNumber(this.previousOperand)} ${this.operation}`
      } else {
        this.previousOperandElem.innerText = ''
      }
      this.currentOperand=this.currentOperand.toString().slice(0,14)
    }
}



const numberButtons=document.querySelectorAll('[number]')
const operationButtons=document.querySelectorAll('[operation]')
const equalsButton=document.querySelector('[equal]')
const deleteButton=document.querySelector('[delete]')
const power_of_twoButton=document.querySelector('[power_of_two]')
const AllClearButton=document.querySelector('[ac]')
const previousOperandElem=document.querySelector('[previous]')
const currentOperandElem=document.querySelector('[current]')

const calculator = new Calculator(previousOperandElem,currentOperandElem)

numberButtons.forEach(button => {
    button.addEventListener('click', () =>{
        calculator.appendNumber(button.innerText)
        calculator.updateOperation()
    })
})

operationButtons.forEach(button => {
    button.addEventListener('click', () => {
      calculator.chooseOperation(button.innerText)
      calculator.updateOperation()
    })
  })

  equalsButton.addEventListener('click', button => {
    calculator.compute()
    calculator.updateOperation()
  })
  
  AllClearButton.addEventListener('click', button => {
    calculator.clear()
    calculator.updateOperation()
  })
  
  deleteButton.addEventListener('click', button => {
    calculator.delete()
    calculator.updateOperation()
  })

  power_of_twoButton.addEventListener('click', button => {
    calculator.power_of_two()
    calculator.updateOperation()
  })

  function changeBodyBg(color){
      document.body.style.background=color;
  }