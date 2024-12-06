import { Button } from '@/components/ui/button';
import Image from 'next/image';

const About = () => {
  return (
    <section className="py-32">
      <div className="container">
        <div className="mx-auto flex max-w-screen-md flex-col gap-8 pb-28 text-center">
          <h1 className="text-4xl font-semibold md:text-7xl">
            Welcome to Our Team
          </h1>
          <p className="text-xl font-medium text-muted-foreground">
            Meet our team, discover our values, and learn how we balance work,
            life, and everything in between.
          </p>
        </div>
        <div className="grid gap-3 md:grid-cols-2 lg:grid-cols-3">
          <Image src="https://images.unsplash.com/photo-1479936343636-73cdc5aae0c3" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-1" width={300} height={300} />
          <Image src="https://images.unsplash.com/photo-1506863530036-1efeddceb993" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-2" width={300} height={300} />
          <Image src="https://images.unsplash.com/photo-1522075469751-3a6694fb2f61" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-3" width={300} height={300} />
          <Image src="https://images.unsplash.com/photo-1531123414780-f74242c2b052" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-4" width={300} height={300} />
          <Image src="https://images.unsplash.com/photo-1509305717900-84f40e786d82" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-5" width={300} height={300} />
          <Image src="https://images.unsplash.com/photo-1521119989659-a83eee488004" className='max-h-80 w-full object-cover h-full rounded-md border hover:scale-105 transition-all saturate-50 hover:saturate-100' alt="team-6" width={300} height={300} />
        </div>
        <div className="mx-auto grid max-w-screen-lg gap-28 py-28 md:grid-cols-2">
          <div>
            <h2 className="mb-5 text-4xl font-semibold">Our Vision</h2>
            <p className="text-xl font-medium leading-8 text-muted-foreground">
              For years, the process of building custom software has remained
              challenging. Today, visual builders exist, but tailored solutions
              still require technical expertise and a lot of time. This is a
              problem for businesses and individuals alike.
              <br />
              <br />
              What if you could create custom software without writing a single
              line of code? What if you could build your own tools.
              <br />
              <br />
              With our platform, you can! Our tools let you design layouts and
              create functionality—all without needing to code.
              <br />
              <br />
              We believe that everyone should be able to build their own
              solutions, regardless of their technical background.
            </p>
          </div>
          <div>
            <h2 className="mb-5 text-4xl font-semibold">Our Creators</h2>
            <p className="text-xl font-medium leading-8 text-muted-foreground">
              <a href="#" className="mr-1 underline">
                Our Company
              </a>
              has been building web tools for over a decade, focusing on
              efficiency and user control in every project. We know that the
              best solutions are the ones that you can create yourself.
              <br />
              <br />
              We initially developed these solutions for our own team, and now
              everyone can benefit from them too. We are proud to offer a
              platform that is accessible to all, regardless of technical
              expertise.
              <br />
              <br />
              Our team is made up of talented individuals who are passionate
              about creating tools that empower users to build their own
              solutions with ease. We are dedicated to helping you achieve your
              goals, and we can’t wait to see what you create!
            </p>
          </div>
        </div>
        <div className="mx-auto flex max-w-screen-lg flex-col items-center justify-between gap-8 rounded-2xl bg-muted/50 p-14 text-center md:flex-row md:text-left">
          <h3 className="text-3xl font-semibold">
            Part of
            <br />
            Our Global Team
          </h3>
          <Button size="lg">Get to know the team</Button>
        </div>
      </div>
    </section>
  );
};

export { About };
