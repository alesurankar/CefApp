import { Logo2 } from '../../../assets/images/images'
import Button from '../../../utils/Button'
import { FacebookIcon, InstagramIcon, LinkedInIcon, TwitterIcon } from '../../../assets/icons/icons'

const Footer = () => {

    const RenderLink = (props: { text: string, className?: string }) => {
        return (
            <p className={`${props.className} text-lg text-textColor font-semibold cursor-pointer`}>{props.text}</p>
        )
    }

    const RenderSocialIcon = (props: { icon: any, className?: string }) => {
        return (
            <div className={`${props.className} shrink-0 cursor-pointer`}>
                <img
                    className='w-full h-full'
                    src={props.icon}
                    alt='Social'
                />
            </div>
        );
    }

    return (
        <footer className='w-screen bg-gray-300 px-8 py-20 lg:p-24 flex flex-col lg:flex-row justify-center lg:justify-between'>
            <div className='flex flex-col lg:w-1/2'>
                <div className='shrink-0 w-40 cursor-pointer'>
                    <img
                        className='w-full h-full'
                        src={Logo2}
                        alt="Logo"
                    />
                </div>
                <div className='my-10 lg:w-[62%]'>
                    <p className='text-lg text-textColor'>Updates right to your Inbox</p>
                    <input
                        className='w-full px-5 py-3 rounded-lg border border-borderColor text-lg text-textColor mt-3 focus:outline-blueColor'
                        type='email'
                        placeholder='Email Address'
                    />
                    <Button
                        title='Send'
                        mainClassName='bg-blueColor w-full mt-5 hover:bg-yellowColor'
                        titleClassName='text-whiteColor'
                    />
                </div>
                <div className='hidden lg:flex'>
                    <ul className='list-none flex items-center gap-7'>
                        <li>
                            <RenderLink text='© 2025' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='Privacy policy' />
                        </li>
                        <li>
                            <RenderLink text='Terms of use' />
                        </li>
                    </ul>
                </div>
            </div>

            <div className='flex flex-col'>

                <div className='hidden lg:flex gap-14'>
                    <ul className='list-none'>
                        <li>
                            <RenderLink text='Our story' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='FAQ' className='font-normal' />
                        </li>
                        <li>
                            <RenderLink text='Contact' className='font-normal' />
                        </li>
                    </ul>

                    <ul className='list-none'>
                        <li>
                            <RenderLink text='Tradition' className='font-normal' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='Health' className='font-normal' />
                        </li>
                        <li>
                            <RenderLink text='Spirit' className='font-normal' />
                        </li>
                    </ul>

                    <ul className='list-none'>
                        <li>
                            <RenderLink text='Training' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='Skills' className='font-normal' />
                        </li>
                        <li>
                            <RenderLink text='Weapons' className='font-normal' />
                        </li>
                    </ul>
                </div>

                <div className='lg:hidden'>
                    <ul className='list-none'>
                        <li>
                            <RenderLink text='Our story' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='Pet care' />
                        </li>
                        <li>
                            <RenderLink text='Shop' />
                        </li>
                    </ul>
                </div>

                <div className='mt-10 lg:hidden'>
                    <ul className='list-none'>
                        <li>
                            <RenderLink text='Terms of use' />
                        </li>
                        <li className='my-5'>
                            <RenderLink text='Privacy policy' />
                        </li>
                        <li>
                            <RenderLink text='© 2025' />
                        </li>
                    </ul>
                </div>

                <div className='flex items-center lg:justify-end gap-5 mt-10 lg:mt-24'>
                    <RenderSocialIcon
                        icon={FacebookIcon}
                    />
                    <RenderSocialIcon
                        icon={LinkedInIcon}
                    />
                    <RenderSocialIcon
                        icon={InstagramIcon}
                    />
                    <RenderSocialIcon
                        icon={TwitterIcon}
                    />
                </div>
            </div>


        </footer>
    )
}

export default Footer