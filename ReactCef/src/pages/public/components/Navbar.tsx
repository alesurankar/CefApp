import { useState, useEffect } from 'react';
import { Logo1 } from '../../../assets/images/images'
import Button from '../../../utils/Button'
import Modal from '../../../utils/Modal'
import AuthForm from './AuthForm'
import api from '../../../utils/api';
import { useNavigate } from "react-router-dom";

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
                <button className="hover:underline" onClick={() => navigate("/")}>
                    Home
                </button>
                <button className="hover:underline" onClick={() => navigate("/page1")}>
                    page1
                </button>
                <button className="hover:underline" onClick={() => navigate("/page2")}>
                    page2
                </button>
                <button className="hover:underline" onClick={() => navigate("/page3")}>
                    page3
                </button>
            {/* Auth Buttons */}
            <div className='flex items-center justify-between'>
            {user ? (
                <Button
                    title='Log out'
                    mainClassName='bg-red-500 hover:bg-red-600'
                    titleClassName='text-3xl text-white font-bold uppercase'
                    onClick={handleLogout}
                />
            ) : (
                <Button
                    title='Log in'
                    mainClassName='bg-[#7c2923] hover:bg-[#d5453a]'
                    titleClassName='text-3xl text-white font-bold uppercase'
                    onClick={() => setShow(true)}
                />
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