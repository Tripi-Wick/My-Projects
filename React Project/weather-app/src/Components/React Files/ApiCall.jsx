async function getWeather(url) {
    try {
        let response = await fetch(url);
        if (response.ok) {
            return await response.json();
        }
        else {
            throw new Error(`HTTP ERROR CODE : ${response.status}`);
        }
    }
    catch (err) {
        console.log('Error During Fetching Data : ', err);
        return null;
    }

}

export default async function ApiCall(location) {
    const apiKey = 'QU6BMCND87XHDRBCFZS8DA2AX'
    let url = `https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/${location}?unitGroup=metric&key=${apiKey}&contentType=json`
    let data = await getWeather(url);
    let info = {};
    if (data) {
        info = {
            add: data.address,
            desc: data.description,
            date: data.days[0].datetime,
            temp: data.days[0].temp,
            tempMax: data.days[0].tempmax,
            tempMin: data.days[0].tempmin,
            feelLike: data.days[0].feelslike,
            condition: data.days[0].conditions,
            humid: data.days[0].humidity
        };
    }else info = null;

    return info;
}