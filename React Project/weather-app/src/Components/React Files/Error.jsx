import Alert from '@mui/material/Alert';
import '../CSS Files/Error.css'
export default function ErrFunc(){
    return(
        <Alert severity="error" className='alert'>NO SUCH PLACE EXISTS.</Alert>
    )
}