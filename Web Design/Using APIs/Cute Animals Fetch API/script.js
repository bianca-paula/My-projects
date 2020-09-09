const cat_result=document.getElementById('cat_element');
const dog_result=document.getElementById('dog_element');
const fox_result=document.getElementById('fox_element');
const cat_button=document.getElementById('cat_button');
const dog_button=document.getElementById('dog_button');
const fox_button=document.getElementById('fox_button');

cat_button.addEventListener('click', get_random_cat)
dog_button.addEventListener('click', get_random_dog)
fox_button.addEventListener('click', get_random_fox)

function get_random_cat(){
    fetch('https://aws.random.cat/meow')
        .then(res => res.json())
        .then(data => {
            cat_result.innerHTML = `<img src="${data.file}"/>`
        })
}

function get_random_dog(){
    fetch('https://random.dog/woof.json')
        .then(res => res.json())
        .then(data => {
            if(data.url.includes('.mp4'))
            {
                get_random_dog()
            }
            else
                {
                    dog_result.innerHTML = `<img src="${data.url}"/>`
                }
        })
}

function get_random_fox(){
    fetch('https://randomfox.ca/floof/')
        .then(res => res.json())
        .then(data => {
            fox_result.innerHTML = `<img src="${data.image}"/>`
        })
}
