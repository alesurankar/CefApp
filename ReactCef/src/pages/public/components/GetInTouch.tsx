import Button from '../../../utils/Button'
import { Fighter } from '../../../assets/images/images'

const GetInTouch = () => {
    return (
        <section className='w-screen bg-gray-500 px-8 py-20 lg:p-24 flex flex-col lg:flex-row items-center justify-center lg:justify-between'>
            <div className='flex flex-col items-center justify-center lg:items-start lg:justify-normal lg:w-1/2'>
                <h1 className='text-5xl text-textColor font-semibold'>{`Let's go!`}</h1>
                <p className='text-lg text-textColor opacity-80 my-10'>{`Dont ask any questions!`}</p>
                <Button
                    title='Get in touch'
                    mainClassName='bg-red-500 hover:bg-red-600'
                    titleClassName='hover:text-whiteColor'
                />
            </div>
            <div className='shrink-0 w-1/4 mt-14 lg:mt-0 lg:w-1/4 lg:h-[460px]'>
                <img
                    className='w-full h-full'
                    src={Fighter}
                    alt='Fighter'
                />
            </div>
        </section>
    )
}

export default GetInTouch