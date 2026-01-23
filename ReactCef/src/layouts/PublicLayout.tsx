import { Outlet } from "react-router-dom";
import Navbar from "../pages/components/Navbar";
import Footer from "../pages/components/Footer";

const PublicLayout = () => {
    return (
        <>
            <Navbar />
            <Outlet />
            <Footer />
        </>
    );
};

export default PublicLayout;