import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';

import ApiCall  from './ApiCall'
import '../CSS Files/Search.css'

import { useState, useEffect } from 'react';


export default function SearchBar({updateInfo}){
    let [query,setQuery] = useState('');

    async function handleClick(event){
        event.preventDefault();
        updateInfo(await ApiCall(query));
        setQuery('');
    }
        
    function handleChange(event){
        setQuery(event.target.value)
    }
    
    async function handleKeyDown(event){
        if(event.key === 'Enter'){
            updateInfo(await ApiCall(query));
            setQuery('');
        }
    }

    return(
        <div className='search'>
        <TextField  className='searchBox' id="outlined-basic" label="Enter Location" variant="outlined" value={query} onChange={handleChange} onKeyDown={handleKeyDown}/>
        <Button className='searchButton' variant="outlined" onClick={handleClick} >Search</Button>
        </div>
    );
}



