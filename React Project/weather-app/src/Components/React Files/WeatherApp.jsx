import Header from './Header'
import SearchBar from './Search'
import ResultBox from './ResultBox'
import ErrFunc from './Error';

import { useEffect, useState } from 'react';



export default function WeatherApp() {
    let [info,setInfo]=useState(null);
    
    function updateInfo(res){
        setInfo(res);
    }  
    
    return (
        <>
            <Header />
            <SearchBar updateInfo ={updateInfo} />
            {info?(info &&<ResultBox info={info}/>):<ErrFunc />}
        </>
    );
}