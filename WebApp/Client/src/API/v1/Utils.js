const handleErrors = (response) => {
    if (!response.ok) {
        throw Error (response.statusText)
    }
    return response
}



export const getResponseData= ( async (request) => {
    return await fetch(request).then(handleErrors)
    .then(response => {
        return response.json().then(data => data)})
    .catch((error) => {
        console.log(error)
        return false
    })
})



