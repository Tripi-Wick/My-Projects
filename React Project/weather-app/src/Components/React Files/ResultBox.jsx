import * as React from 'react';
import Card from '@mui/material/Card';
import CardContent from '@mui/material/CardContent';
import CardMedia from '@mui/material/CardMedia';

import '../CSS Files/ResultBox.css'
import WbSunnyIcon from '@mui/icons-material/WbSunny';
import AcUnitIcon from '@mui/icons-material/AcUnit';
import ThunderstormIcon from '@mui/icons-material/Thunderstorm';

const Heat = "https://img.freepik.com/free-photo/sunny-meadow-landscape_1112-134.jpg?t=st=1722887594~exp=1722891194~hmac=34bf3593cb3370f81a04210135b26bc1d6a494da466f1115255f4478e70bbe92&w=1480"
const Cold = "https://img.freepik.com/free-photo/forest-mountain-ridge-covered-with-snow-milky-way-starry-sky-christmas-winter-night_146671-14693.jpg?t=st=1722887946~exp=1722891546~hmac=698ceedce352a15c8fa44f6b5e059cb6f573b749de50811eb969793a7e9fcf15&w=1060"
const Rain = "https://img.freepik.com/free-photo/photorealistic-view-tree-nature-with-branches-trunk_23-2151478106.jpg?t=st=1722825958~exp=1722829558~hmac=9e20306115c7340cabbdeb88897149a3ac99ff9647f7e38050e4af535c4a8cce&w=1800";


export default function ResultBox({ info }) {
    return (
        <div className='resCardBox'>
            <Card sx={{ width: 700, height: 750 }}>
                <CardMedia
                    className='img'
                    component="img"
                    alt="Weather Img"
                    height="300"
                    image= {
                        info.humid > 70
                            ? (Rain)
                            : info.temp > 20 
                            ? (Heat)
                            : info.temp < 20
                            ? (Cold):null
                    }
                />

                <CardContent className='cardContent'>

                    <div className='title'>
                        <h4>{info.add} </h4>
                        {
                            info.humid > 70
                            ? (<ThunderstormIcon style={{ fontSize: '3rem', padding: '.6rem', marginLeft: '.8rem' }} />)
                            : info.temp > 20 
                            ? (<WbSunnyIcon style={{ fontSize: '3rem', padding: '.6rem', marginLeft: '.8rem' }} />)
                            : info.temp < 20
                            ? (<AcUnitIcon style={{ fontSize: '3rem', padding: '.6rem', marginLeft: '.8rem' }}/>):null
                        }
                    </div>

                    <div className='details'>
                        <span className='day'>
                            <p className='date'>{info.date}</p>
                            <p className='temp'>{info.temp} &deg;C</p>
                        </span>
                        <hr />
                        <span className='tempVar'>
                            <p className='maxT'>Max Temp : {info.tempMax}&deg;C</p>
                            <p className='minT'>Min Temp : {info.tempMin}&deg;C</p>
                        </span>
                        <hr />
                        <span className='extraInfo'>
                            <p className='cond'>{info.condition}</p>
                            <p className='feels'>Feels Like : {info.tempMin}</p>
                        </span>
                        <hr />
                        <p className='desc'>{info.desc}</p>
                    </div>
                </CardContent>

            </Card>
        </div>
    );
}
