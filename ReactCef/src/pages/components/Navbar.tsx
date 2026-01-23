import { useNavigate } from "react-router-dom";

const Navbar = () => {
    const navigate = useNavigate();

    return (
        <nav className='w-screen p-6 bg-green-100 lg:px-24 lg:py-8 lg:flex lg:items-center lg:justify-between'>
            {/* Logo Section */}
            <div className='shrink-0 w-40 cursor-pointer'>
                <img
                    className='w-full h-full'
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
            (
                <button></button>
            )
            </div>
        </nav>
    )
}

export default Navbar