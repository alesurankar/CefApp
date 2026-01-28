import { IntroVideo } from '../../../assets/videos/videos'

const Video = () => {
    return (
        <section className='w-screen bg-[#4a5748] px-8 py-20 lg:p-24 flex flex-col items-center justify-center'>
            <video
                className='rounded-lg w-full h-full object-cover lg:w-1/2'
                src={IntroVideo}
                loop
                controls
                playsInline
                muted
                //autoPlay
            />
        </section>
    )
}

export default Video