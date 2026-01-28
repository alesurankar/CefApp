import { Outlet } from "react-router-dom";
import Navbar from "../pages/public/components/Navbar";
import Footer from "../pages/public/components/Footer";

interface PublicLayoutProps {
  user: any;
  setUser: (user: any) => void;
}

const PublicLayout = ({ user, setUser }: PublicLayoutProps) => {
  return (
    <>
      <Navbar user={user} setUser={setUser} />
      <Outlet context={{ user, setUser }} />
      <Footer />
    </>
  );
};

export default PublicLayout;
