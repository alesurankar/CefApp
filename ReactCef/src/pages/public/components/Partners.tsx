import { useState } from "react";
import { Tools } from '../../../assets/images/images'

const Partners = () => {
    const [isOpen, setIsOpen] = useState(false);
    

    return (
        <div className="relative w-full">
            {/* Toggle Button */}
            <button
                className="bg-green-500 text-white px-4 py-2 rounded shadow"
                onClick={() => setIsOpen((prev) => !prev)}
            >
                {isOpen ? "Hide Tools" : "Show Tools"}
            </button>

            {/* Collapsible Content */}
            <div
                className={`transition-all duration-300 overflow-hidden ${
                isOpen ? "max-h-96 mt-4" : "max-h-0"
                }`}
            >
                <div className="p-4 bg-gray-200 rounded shadow">
                {/* Your tools content goes here */}
                <Tool1 />
                </div>
            </div>
        </div>
        );
    };



const Tool1 = () => {
    return (
        <section className='w-screen bg-whiteColor px-8 py-20 lg:p-24 flex items-center justify-center'>
            <div className='shrink-0 w-full lg:hidden'>
                <img
                    className='w-full h-full'
                    src={Tools}
                    alt='Partners'
                />
            </div>
            <div className='shrink-0 hidden lg:flex'>
                <img
                    className='w-full h-full'
                    src={Tools}
                    alt='Partners'
                />
            </div>
        </section>
    )
}

export default Partners