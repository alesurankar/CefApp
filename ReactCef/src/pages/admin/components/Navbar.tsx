import { useState } from 'react'
import Button from '../../../utils/Button'
import Modal from '../../../utils/Modal'
import AddItemForm from './AddItemForm'


const Navbar = () => {
    const [show, setShow] = useState(false);

    return (
        <nav className='w-screen p-6 bg-green-100 lg:px-24 lg:py-8 lg:flex lg:items-center lg:justify-between'>
            
            {/* Auth Buttons */}
            <div className='flex items-center justify-between'>     
                <Button
                    title='add item'
                    mainClassName='bg-red-800 hover:bg-red-700'
                    titleClassName='text-xl text-white'
                    onClick={() => setShow(true)}
                />
            </div>
            {/* Modal */}
            {show && (
                <Modal onClose={() => setShow(false)} maxWidth="max-w-xl" padding="p-6">
                    <AddItemForm onSuccess={() => setShow(false)} />
                </Modal>
            )}
        </nav>
    )
}

export default Navbar