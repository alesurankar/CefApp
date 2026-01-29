import { useState, useEffect } from 'react';
import { Logo1 } from '../../../assets/images/images'
import Modal from '../../../utils/Modal'
import AuthForm from './AuthForm'
import api from '../../../utils/api';
import { useNavigate } from "react-router-dom";
import MyLink from '../../../utils/MyLink';
import Button from '../../../utils/Button';

interface NavbarProps {
  user: any;
  setUser: (user: any) => void;
}

const Navbar = ({ user,setUser }: NavbarProps) => {
    const navigate = useNavigate();
    const [show, setShow] = useState(false);
    
    useEffect(() => {
        api.get("/me")
        .then(res => setUser(res.data.user))
        .catch(() => setUser(null));
    }, [setUser]);

    const handleLogout = async () => {
        try {
            await api.get("/logout");
            setUser(null);
        } 
        catch (err) {
            console.error("Logout failed", err);
        }
    };

    return (
        <nav className='w-screen p-6 bg-green-100 lg:px-24 lg:py-8 lg:flex lg:items-center lg:justify-between'>
            {/* Logo Section */}
            <div className='shrink-0 w-40 cursor-pointer'>
                <img
                    className='w-full h-full'
                    src={Logo1}
                    alt="Logo"
                />
            </div>
                <MyLink title="Home" onClick={() => navigate("/")}/>
                <MyLink title="Page1" onClick={() => navigate("/page1")}/>
                <MyLink title="Page2" onClick={() => navigate("/page2")}/>
                <MyLink title="Page3" onClick={() => navigate("/page3")}/>
            {/* Auth Buttons */}
            <div className='flex items-center justify-between'>
            {user ? (
                <Button type="button" title="Log Out" 
                    MyClassName='text-[1.4rem] font-bold uppercase' 
                    onClick={handleLogout}/>
            ) : (
                <Button type="button" title="Log In" 
                    MyClassName='text-[1.4rem] font-bold uppercase' 
                    onClick={() => setShow(true)}/> 
            )}
            </div>
            {/* Modal */}
            {show && (
                <Modal onClose={() => setShow(false)} maxWidth="max-w-3xl">
                    <AuthForm onSuccess={() => setShow(false)} setUser={setUser} />
                </Modal>
            )}
        </nav>
    )
}

export default Navbar