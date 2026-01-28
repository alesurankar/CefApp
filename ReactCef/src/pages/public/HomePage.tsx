/**
 * Component that renders the complete landing page
 * Organizes all sections from top to bottom
 */

import { useOutletContext } from "react-router-dom";
import Hero from './components/Hero'
import Partners from './components/Partners'
import GetInTouch from './components/GetInTouch'
import Fetch from './components/Fetch'

const HomePage = () => {
  const { user } = useOutletContext<{
    user: any;
    setUser: (user: any) => void;
  }>();

  return (
    <div className='main'>
      <Hero user={user}/>
      
      <Partners />

      {!user && <GetInTouch />}
      
      {user && <Fetch user={user}/>}
    </div>
  )
}

export default HomePage