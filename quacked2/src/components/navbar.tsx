'use client';

import {
  AppWindow,
  ArrowLeft,
  ArrowRight,
  ArrowRightLeft,
  Book,
  Building,
  Building2,
  Calculator,
  Calendar,
  CheckCircle2,
  Clock,
  Code,
  Computer,
  DollarSign,
  File,
  Flag,
  Gavel,
  Globe,
  Globe2,
  Lightbulb,
  Lock,
  Menu,
  Mic,
  Newspaper,
  Phone,
  PieChart,
  Play,
  PlayCircle,
  Puzzle,
  Pyramid,
  Rocket,
  Scale,
  Search,
  ShieldCheck,
  Speech,
  Table,
  UserPlus,
  UserRound,
  Users,
  X,
} from 'lucide-react';
import { Fragment, useState } from 'react';

import { Button } from '@/components/ui/button';
import {
  NavigationMenu,
  NavigationMenuContent,
  NavigationMenuItem,
  NavigationMenuLink,
  NavigationMenuList,
  NavigationMenuTrigger,
} from '@/components/ui/navigation-menu';
import { ModeToggle } from './ui/mode-toggle';

const solutions = [
  {
    id: 'solution-1',
    title: 'Ea Sit In Eu',
    description: 'Lorem ipsum dolor sit amet.',
    href: '#',
    subpages: [
      {
        id: 'subpage-1',
        title: 'Consectetur Adipiscing',
        href: '#',
        icon: File,
      },
      {
        id: 'subpage-2',
        title: 'Maecenas Scelerisque',
        href: '#',
        icon: Building,
      },
      {
        id: 'subpage-3',
        title: 'Magna in Bulputate',
        href: '#',
        icon: Search,
      },
      {
        id: 'subpage-4',
        title: 'Duis Sit Id',
        href: '#',
        icon: File,
      },
      {
        id: 'subpage-5',
        title: 'Sed et Nulla',
        href: '#',
        icon: UserPlus,
      },
    ],
  },
  {
    id: 'solution-2',
    title: 'Aenean Sed',
    description: 'Odio molestie tincidunt et id nunc.',
    href: '#',
    subpages: [
      {
        id: 'subpage-6',
        title: 'Turpis Imperdiet',
        href: '#',
        icon: CheckCircle2,
      },
      {
        id: 'subpage-7',
        title: 'Id Occaecat Elit',
        href: '#',
        icon: UserRound,
      },
      {
        id: 'subpage-8',
        title: 'Ut Est Cillum',
        href: '#',
        icon: ShieldCheck,
      },
      {
        id: 'subpage-9',
        title: 'Non Id Irure',
        href: '#',
        icon: Scale,
      },
      {
        id: 'subpage-10',
        title: 'Anim Sit Minim',
        href: '#',
        icon: Globe,
      },
    ],
  },
  {
    id: 'solution-3',
    title: 'Ea Ea Et Irure',
    description: 'Minim irure id nostrud pariatur.',
    href: '#',
    subpages: [
      {
        id: 'subpage-11',
        title: 'Ex Aliqua Duis',
        href: '#',
        icon: Globe2,
      },
      {
        id: 'subpage-12',
        title: 'Sit Non Eu Laborum',
        href: '#',
        icon: Clock,
      },
      {
        id: 'subpage-13',
        title: 'Aute exercitation',
        href: '#',
        icon: DollarSign,
      },
      {
        id: 'subpage-14',
        title: 'Consequat Ex',
        href: '#',
        icon: Phone,
      },
      {
        id: 'subpage-15',
        title: 'Deserunt Ea.',
        href: '#',
        icon: Speech,
      },
    ],
  },
  {
    id: 'solution-4',
    title: 'Pariatur Aliquip Aliqua',
    description: 'Fugiat magna cillum in laboris labore duis.',
    href: '#',
    subpages: [
      {
        id: 'subpage-16',
        title: 'Laboris Ad Elit',
        href: '#',
        icon: PieChart,
      },
      {
        id: 'subpage-17',
        title: 'Amet Minim Sunt Sint',
        href: '#',
        icon: Calculator,
      },
      {
        id: 'subpage-18',
        title: 'Laborum Aliquip Cillum',
        href: '#',
        icon: Table,
      },
    ],
  },
];

const solutionTechnologies = [
  {
    id: 'technology-1',
    title: 'Consectetur Labore',
    href: '#',
    icon: Puzzle,
  },
  {
    id: 'technology-2',
    title: 'Aliqua Enim',
    href: '#',
    icon: Lock,
  },
  {
    id: 'technology-3',
    title: 'Dolor Minim',
    href: '#',
    icon: Code,
  },
];

const productCategories = [
  {
    title: 'Commodo Adipisicing',
    products: [
      {
        id: 'product-1',
        title: 'Consectetur Nostrud',
        description: 'Dolore ad in eu esse.',
        href: '#',
        image: 'https://www.shadcnblocks.com/images/block/block-1.svg',
      },
      {
        id: 'product-2',
        title: 'Et Aliqua',
        description: 'Voluptate deserunt minim.',
        href: '#',
        image: 'https://www.shadcnblocks.com/images/block/block-2.svg',
      },
      {
        id: 'product-3',
        title: 'Deserunt',
        description: 'Velit excepteur tempor.',
        href: '#',
        image: 'https://www.shadcnblocks.com/images/block/block-3.svg',
      },
    ],
  },
  {
    title: 'Nostrud Veniam',
    products: [
      {
        id: 'product-4',
        title: 'Id Qui Deserunt',
        description: 'Non voluptate enim consequat occaecat qui .',
        href: '#',
        image: 'https://www.shadcnblocks.com/images/block/block-4.svg',
      },
      {
        id: 'product-5',
        title: 'Aliqua Ullamco Voluptate',
        description: 'Mollit anim tempor sunt est duis.',
        href: '#',
        image: 'https://www.shadcnblocks.com/images/block/block-5.svg',
      },
    ],
  },
];

const globalCategories = [
  {
    title: 'Qui Deserunt',
    features: [
      {
        id: 'feature-1',
        title: 'Dolore Laboris',
        description: 'Commodo ea et enim mollit occaecat commodo duis .',
        href: '#',
        icon: Rocket,
      },
      {
        id: 'feature-2',
        title: 'Magna Cupidatat',
        description:
          'Incididunt fugiat deserunt laborum ex pariatur irure occaecat.',
        href: '#',
        icon: Building2,
      },
      {
        id: 'feature-3',
        title: 'Dolore Voluptate Dolore',
        description: 'Duis sint culpa labore fugiat ipsum nisi.',
        href: '#',
        icon: Globe2,
      },
    ],
  },
  {
    title: 'Quis Et Deserunt',
    features: [
      {
        id: 'feature-4',
        title: 'Culpa Voluptate',
        description: 'Amet ullamco reprehenderit in elit.',
        href: '#',
        icon: Phone,
      },
      {
        id: 'feature-5',
        title: 'Sit Labore',
        description: 'Anim quis do et ullamco.',
        href: '#',
        icon: Gavel,
      },
      {
        id: 'feature-6',
        title: 'Irure Qui Lorem',
        description: 'Sit ex consectetur et tempor.',
        href: '#',
        icon: DollarSign,
      },
      {
        id: 'feature-7',
        title: 'Velit Minim',
        description:
          'Voluptate est pariatur deserunt ad ad voluptate laboris tempor.',
        href: '#',
        icon: Computer,
      },
      {
        id: 'feature-8',
        title: 'Culpa Proident',
        description: 'Enim nostrud occaecat voluptate et cillum ipsum.',
        href: '#',
        icon: Flag,
      },
    ],
  },
];

const regions = [
  {
    title: 'Asia-Pacific',
    locations: [
      {
        title: 'China',
        href: '#',
        icon: '🇨🇳',
      },
      {
        title: 'India',
        href: '#',
        icon: '🇮🇳',
      },
      {
        title: 'Japan',
        href: '#',
        icon: '🇯🇵',
      },
      {
        title: 'Thailand',
        href: '#',
        icon: '🇹🇭',
      },
    ],
  },
  {
    title: 'Europe',
    locations: [
      {
        title: 'Italy',
        href: '#',
        icon: '🇮🇹',
      },
      {
        title: 'Germany',
        href: '#',
        icon: '🇩🇪',
      },
      {
        title: 'Poland',
        href: '#',
        icon: '🇵🇱',
      },
      {
        title: 'United Kingdom',
        href: '#',
        icon: '🇬🇧',
      },
    ],
  },
  {
    title: 'Americas',
    locations: [
      {
        title: 'Brazil',
        href: '#',
        icon: '🇧🇷',
      },
      {
        title: 'Canada',
        href: '#',
        icon: '🇨🇦',
      },
      {
        title: 'Mexico',
        href: '#',
        icon: '🇲🇽',
      },
      {
        title: 'United States',
        href: '#',
        icon: '🇺🇸',
      },
    ],
  },
  {
    title: 'Middle East/Africa',
    locations: [
      {
        title: 'Egypt',
        href: '#',
        icon: '🇸🇦',
      },
      {
        title: 'Nigeria',
        href: '#',
        icon: '🇳🇬',
      },
      {
        title: 'Türkiye',
        href: '#',
        icon: '🇹🇷',
      },
      {
        title: 'United Arab Emirates',
        href: '#',
        icon: '🇦🇪',
      },
    ],
  },
];

const resources = [
  {
    id: 'resource-1',
    title: 'Ea Incididunt',
    description: 'Voluptate aute tempor.',
    href: '#',
    icon: Calendar,
  },
  {
    id: 'resource-2',
    title: 'Veniam',
    description: 'Cupidatat ut enim eiusmod dolore.',
    href: '#',
    icon: Mic,
  },
  {
    id: 'resource-3',
    title: 'Fugiat Exercitation',
    description: 'Est reprehenderit aliqua nisi consectetur.',
    href: '#',
    icon: Newspaper,
  },
  {
    id: 'resource-4',
    title: 'Consequat',
    description: 'Ad eu ea duis culpa aliquip.',
    href: '#',
    icon: PlayCircle,
  },
  {
    id: 'resource-5',
    title: 'Tempor',
    description: 'Ea consequat commodo esse commodo.',
    href: '#',
    icon: Book,
  },
  {
    id: 'resource-6',
    title: 'Pariatur',
    description: 'Qui aliquip consectetur ad anim do.',
    href: '#',
    icon: Lightbulb,
  },
];

const topicGroups = [
  {
    title: 'Ut consectetur',
    topics: [
      {
        id: 'topic-1',
        title: 'Est Incididunt Commodo',
        href: '#',
        icon: Globe,
      },
      {
        id: 'topic-2',
        title: 'Proident Non Id Mollit',
        href: '#',
        icon: Rocket,
      },
      {
        id: 'topic-3',
        title: 'Magna Excepteur',
        href: '#',
        icon: Pyramid,
      },
      {
        id: 'topic-4',
        title: 'Reprehenderit',
        href: '#',
        icon: ArrowRightLeft,
      },
      {
        id: 'topic-5',
        title: 'Sit Fugiat',
        href: '#',
        icon: AppWindow,
      },
    ],
  },
  {
    title: 'Non Consectetur',
    topics: [
      {
        id: 'topic-6',
        title: 'Culpa',
        href: '#',
        icon: Play,
      },
    ],
  },
];

const SolutionsMenu = () => (
  <div className="grid gap-8 sm:grid-cols-2">
    <NavigationMenuLink
      href="#"
      className="group relative flex h-full overflow-hidden rounded-lg bg-primary px-0 pt-8 text-primary-foreground lg:rounded-xl lg:px-6"
    >
      <div className="relative flex w-full flex-col space-y-12 text-left md:space-y-8 lg:w-full lg:flex-row lg:justify-between lg:space-x-6 lg:space-y-0 xl:space-x-12">
        <div className="relative flex flex-col px-6 lg:mb-6 lg:px-0">
          <span className="mb-6 text-xs font-medium uppercase tracking-wider md:mb-8">
            Incididunt
          </span>
          <div className="mt-auto flex items-center space-x-1 text-xs">
            Aute Laboris
            <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
          </div>
          <p className="mt-2 text-xs text-primary-foreground/85">
            Lorem commodo nisi culpa in amet id non eiusmod velit magna commodo
            do ullamco.
          </p>
        </div>
        <div className="relative aspect-[2/1] text-clip rounded-t pl-6 lg:max-w-[22rem] lg:pl-0">
          <img
            src="https://www.shadcnblocks.com/images/block/placeholder-1.svg"
            alt="placeholder"
            className="aspect-[2/1] size-full translate-y-px object-cover object-center"
          />
        </div>
      </div>
    </NavigationMenuLink>
    <div className="order-last mt-3 sm:order-none sm:mt-0 sm:py-2 md:p-6">
      <div className="mb-4 text-left leading-none md:col-span-2 lg:col-span-4 lg:mb-6">
        <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
          Anim Sit Minim
        </strong>
      </div>
      <div className="grid gap-4 lg:grid-cols-2">
        {solutionTechnologies.map((technology) => (
          <NavigationMenuLink
            key={technology.id}
            href="#"
            className="group flex items-center space-x-4 rounded-md bg-accent px-6 py-5 text-left text-foreground/85 hover:text-foreground sm:rounded-none sm:bg-transparent sm:p-0"
          >
            <technology.icon className="size-4" />
            <div className="flex-1 text-sm font-medium">{technology.title}</div>
            <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
          </NavigationMenuLink>
        ))}
      </div>
    </div>
    <div className="col-span-full grid grid-cols-1 gap-6 md:grid-cols-2 lg:grid-cols-4 lg:gap-8">
      {solutions.map((solution) => (
        <div key={solution.id} className="rounded-md border border-border p-5">
          <div className="border-b border-border pb-4">
            <NavigationMenuLink
              href={solution.href}
              className="group flex flex-col text-left"
            >
              <div className="flex items-center">
                <strong className="text-sm font-medium">
                  {solution.title}
                </strong>
                <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
              </div>
              <p className="mt-1 text-xs text-muted-foreground">
                {solution.description}
              </p>
            </NavigationMenuLink>
          </div>
          <menu className="mt-6 grid gap-y-4">
            {solution.subpages.map((subpage) => (
              <NavigationMenuLink
                key={subpage.id}
                href={subpage.href}
                className="group flex items-center space-x-4 text-left text-foreground/85 hover:text-foreground lg:space-x-4 lg:border-0 lg:py-0"
              >
                <subpage.icon className="size-4" />
                <div className="flex-1 text-sm font-medium">
                  {subpage.title}
                </div>
                <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
              </NavigationMenuLink>
            ))}
          </menu>
        </div>
      ))}
    </div>
  </div>
);

const ProductsMenu = () => (
  <div className="grid gap-y-12 lg:flex lg:space-x-8">
    <div className="w-full shrink-0 lg:max-w-72">
      <NavigationMenuLink
        href="#"
        className="group relative flex h-full overflow-hidden rounded-lg bg-primary px-0 py-8 text-primary-foreground lg:rounded-xl lg:px-6"
      >
        <div className="absolute inset-0 bg-accent invert"></div>
        <div className="relative z-10 flex w-full flex-col space-y-12 text-left lg:space-y-0">
          <div className="relative flex aspect-[2/1] max-h-44 w-full flex-1 justify-center invert">
            <img
              src="https://www.shadcnblocks.com/images/block/placeholder-1.svg"
              alt="placeholder"
              className="size-full object-cover object-center"
            />
            <div className="absolute inset-0 bg-[linear-gradient(hsl(var(--accent))_0%,transparent_50%,hsl(var(--accent))_100%)]"></div>
          </div>
          <div className="relative z-20 flex flex-col px-6 lg:px-0">
            <div className="mt-auto flex items-center space-x-1 text-xs">
              Cupidatat Magna Officia
              <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
            </div>
            <p className="mt-2 text-xs text-primary-foreground/85">
              Voluptate nostrud duis labore veniam.
            </p>
          </div>
        </div>
      </NavigationMenuLink>
    </div>
    <div className="grid w-full gap-y-12 lg:gap-y-6">
      {productCategories.map((category) => (
        <div key={category.title} className="grid gap-y-2 lg:gap-y-6">
          <div className="border-border text-left lg:border-b lg:pb-3">
            <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
              {category.title}
            </strong>
          </div>
          <menu className="grid md:grid-cols-3 md:gap-x-5 lg:gap-y-7">
            {category.products.map((product) => (
              <NavigationMenuLink
                key={product.id}
                href="#"
                className="group flex items-center space-x-6 border-b border-border py-5 text-left sm:py-7 lg:space-x-4 lg:border-0 lg:py-0"
              >
                <div className="relative flex aspect-square w-6 shrink-0 items-center justify-center text-clip rounded md:size-9 md:p-2">
                  <img src={product.image} alt={product.title} />
                </div>
                <div className="flex-1">
                  <div className="text-sm font-medium text-foreground/85 group-hover:text-foreground">
                    {product.title}
                  </div>
                  <p className="mt-1 text-xs text-muted-foreground group-hover:text-foreground">
                    {product.description}
                  </p>
                </div>
                <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
              </NavigationMenuLink>
            ))}
          </menu>
        </div>
      ))}
    </div>
  </div>
);

const GlobalGuidanceMenu = () => (
  <div>
    <div className="space-y-6 lg:flex lg:space-x-8 lg:space-y-0">
      <div className="w-full shrink-0 lg:max-w-72">
        <NavigationMenuLink
          href="#"
          className="group relative flex h-full overflow-hidden rounded-lg bg-primary p-0 text-primary-foreground lg:rounded-xl"
        >
          <div className="relative z-10 flex w-full flex-col-reverse text-left lg:flex-col">
            <div className="relative flex aspect-[4/3] max-h-72 w-full flex-1 justify-center">
              <img
                src="https://www.shadcnblocks.com/images/block/placeholder-3.svg"
                alt="placeholder"
                className="size-full object-cover object-center"
              />
            </div>
            <div className="relative z-20 flex flex-col p-6">
              <div className="mt-auto flex items-center space-x-1 text-xs">
                Incididunt
                <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
              </div>
              <p className="mt-2 text-xs">
                Nostrud deserunt fugiat dolor Lorem pariatur et.
              </p>
            </div>
          </div>
        </NavigationMenuLink>
      </div>
      <div className="grid w-full gap-y-12 lg:gap-y-6">
        {globalCategories.map((category) => (
          <div key={category.title} className="grid gap-y-2 lg:gap-y-6">
            <div className="border-border text-left lg:border-b lg:pb-3">
              <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
                {category.title}
              </strong>
            </div>
            <menu className="grid md:grid-cols-3 md:gap-x-6 lg:gap-y-6">
              {category.features.map((feature) => (
                <NavigationMenuLink
                  key={feature.id}
                  href="#"
                  className="group flex items-center space-x-4 border-b border-border py-5 text-left sm:py-7 lg:border-0 lg:py-0"
                >
                  <div className="flex aspect-square size-9 shrink-0 items-center justify-center">
                    <feature.icon className="size-5" />
                  </div>
                  <div className="flex-1">
                    <div className="text-sm font-medium text-foreground/85 group-hover:text-foreground">
                      {feature.title}
                    </div>
                    <p className="mt-1 text-xs text-muted-foreground group-hover:text-foreground">
                      {feature.description}
                    </p>
                  </div>
                  <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
                </NavigationMenuLink>
              ))}
            </menu>
          </div>
        ))}
      </div>
    </div>
    <div className="mt-8">
      <div className="mb-6 border-border pb-1 text-left lg:border-b">
        <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
          Popular Locations
        </strong>
      </div>
      <div className="grid gap-6 md:grid-cols-3 lg:grid-cols-4">
        {regions.map((region) => (
          <div
            key={region.title}
            className="space-y-6 rounded-md border border-border p-6 lg:border-0 lg:p-0"
          >
            <div className="text-left text-xs text-muted-foreground">
              {region.title}
            </div>
            <menu className="grid gap-y-3 border-t border-border pt-6 lg:border-0 lg:pt-0">
              {region.locations.map((location) => (
                <NavigationMenuLink
                  key={location.title}
                  href={location.href}
                  className="group flex items-center space-x-4 text-left text-foreground/85 hover:text-foreground lg:space-x-4 lg:border-0 lg:py-0"
                >
                  <div className="flex size-4 items-center justify-center">
                    {location.icon}
                  </div>
                  <div className="flex-1 text-sm font-medium">
                    {location.title}
                  </div>
                  <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
                </NavigationMenuLink>
              ))}
            </menu>
          </div>
        ))}
      </div>
    </div>
  </div>
);

const CustomersMenu = () => (
  <div className="md:grid-col-2 grid gap-y-8 md:gap-x-6 lg:grid-cols-4">
    <div className="md:col-span-2">
      <NavigationMenuLink
        href="#"
        className="group relative flex h-full overflow-hidden rounded-lg bg-accent p-0 text-accent-foreground sm:pl-6 md:pr-6 lg:rounded-xl lg:px-6"
      >
        <div className="relative z-10 flex w-full flex-col text-left sm:flex-row sm:items-end sm:justify-between">
          <div className="relative z-20 flex max-w-72 flex-col py-6 pb-10 pl-6 sm:pb-6 sm:pl-0 sm:pt-16 md:max-w-64 lg:pt-6">
            <div className="mt-auto flex items-center space-x-1 text-xs font-medium">
              Labore Veniam
              <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
            </div>
            <p className="mt-2 text-xs">
              Velit ut ex enim ullamco esse laboris in fugiat eu mollit.
            </p>
          </div>
          <div className="flex h-full border-t border-border sm:mr-[20%] sm:w-[110px] sm:border-none">
            <div className="relative grid w-1/2 border-x border-border sm:w-full">
              <div className="relative flex items-center justify-center border-b p-4">
                <img
                  src="https://www.shadcnblocks.com/images/block/logos/astro.svg"
                  alt="placeholder"
                  className="h-4 w-full"
                />
                <div className="absolute left-0 top-0 flex translate-x-[-50%] translate-y-[-50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute right-0 top-0 flex translate-x-[50%] translate-y-[-50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
              </div>
              <div className="relative flex items-center justify-center border-b p-4">
                <img
                  src="https://www.shadcnblocks.com/images/block/logos/vercel.svg"
                  alt="placeholder"
                  className="h-4 w-full"
                />
                <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
              </div>
              <div className="relative flex items-center justify-center border-b p-4">
                <img
                  src="https://www.shadcnblocks.com/images/block/logos/shadcn-ui.svg"
                  alt="placeholder"
                  className="h-4 w-full"
                />
                <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
              </div>
              <div className="relative flex items-center justify-center p-4">
                <img
                  src="https://www.shadcnblocks.com/images/block/logos/supabase.svg"
                  alt="placeholder"
                  className="h-4 w-full"
                />
                <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
                <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-accent p-2">
                  <div className="size-1 rounded-full bg-border"></div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </NavigationMenuLink>
    </div>
    <NavigationMenuLink
      href="#"
      className="group text-clip rounded-lg bg-primary text-primary-foreground lg:flex lg:flex-col-reverse lg:rounded-xl"
    >
      <div className="mt-6 px-6 pb-6 text-left lg:mt-12 lg:pb-6">
        <span className="inline-block max-w-48 text-xs/5 font-medium">
          Sunt Elit Pariatur Eu Cillum Laborum Minim Magna
        </span>
      </div>
      <div className="mb-6 flex whitespace-nowrap lg:mb-0">
        <div className="flex w-full border-y border-primary-foreground/15"></div>
        <div className="relative flex aspect-[12/5] w-full max-w-48 shrink-0 items-center justify-center border border-primary-foreground/15">
          <div className="absolute left-0 top-0 flex translate-x-[-50%] translate-y-[-50%] items-center justify-center bg-primary p-2">
            <div className="size-1 rounded-full bg-primary-foreground"></div>
          </div>
          <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-primary p-2">
            <div className="size-1 rounded-full bg-primary-foreground"></div>
          </div>
          <img
            src="https://www.shadcnblocks.com/images/block/logos/astro.svg"
            alt="placeholder"
            className="w-1/2 object-contain object-center opacity-100 invert transition-all duration-100 group-hover:scale-110"
          />
        </div>
        <div className="flex w-full border-y border-primary-foreground/15"></div>
      </div>
    </NavigationMenuLink>
    <div className="col-span-1">
      <NavigationMenuLink
        href="#"
        className="group flex h-full flex-col-reverse overflow-hidden rounded-lg bg-accent text-accent-foreground md:flex-col lg:rounded-xl"
      >
        <div className="mb-5 flex justify-between border-y border-border pl-6 md:mb-0 md:mt-12">
          <div className="relative aspect-square w-16 border-x border-border p-4">
            <img
              src="https://www.shadcnblocks.com/images/block/block-1.svg"
              alt="placeholder"
              className="h-auto w-full object-contain"
            />
            <div className="absolute left-0 top-0 flex translate-x-[-50%] translate-y-[-50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
            <div className="absolute right-0 top-0 flex translate-x-[50%] translate-y-[-50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
            <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
            <div className="absolute bottom-0 right-0 flex translate-x-[50%] translate-y-[50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
          </div>
          <div className="relative aspect-square w-16 border-l border-border p-4">
            <div className="absolute left-0 top-0 flex translate-x-[-50%] translate-y-[-50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
            <div className="absolute bottom-0 left-0 flex translate-x-[-50%] translate-y-[50%] items-center justify-center bg-accent p-2">
              <div className="size-1 rounded-full bg-border"></div>
            </div>
          </div>
        </div>
        <div className="p-6 text-left md:mt-auto">
          <div className="mt-auto flex items-center space-x-1 text-xs font-medium">
            Dolore Laboris
            <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
          </div>
          <p className="mt-2 text-xs text-muted-foreground">
            Esse ipsum reprehenderit mollit.
          </p>
        </div>
      </NavigationMenuLink>
    </div>
  </div>
);

const PartnersMenu = () => (
  <div className="grid gap-y-6 md:grid-cols-2 md:gap-x-6 lg:grid-cols-4">
    <div className="md:col-span-2">
      <NavigationMenuLink
        href="#"
        className="group relative flex h-full overflow-hidden rounded-lg bg-primary p-0 text-primary-foreground lg:rounded-xl"
      >
        <div className="relative z-10 flex w-full flex-col-reverse text-left">
          <div className="relative z-20 flex flex-col px-6 pb-56 pt-6 md:pb-6 md:pt-40">
            <div className="mt-auto flex items-center space-x-1 text-xs font-medium">
              Irure Aute
              <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
            </div>
            <p className="mt-2 text-xs">
              Proident nulla laborum ad minim non culpa dolore dolore sint sit
              in laborum.
            </p>
          </div>
          <div className="absolute inset-0 top-[32%] bg-accent invert md:top-0">
            <img
              src="https://www.shadcnblocks.com/images/block/placeholder-1.svg"
              alt="placeholder"
              className="object-fit size-full object-right-top opacity-100 md:h-2/3 md:object-top"
            />
          </div>
        </div>
      </NavigationMenuLink>
    </div>
    <div className="md:col-span-1">
      <NavigationMenuLink
        href="#"
        className="group relative flex h-full overflow-hidden rounded-lg bg-accent p-0 text-accent-foreground lg:rounded-xl"
      >
        <div className="relative z-10 flex w-full flex-col-reverse text-left">
          <div className="relative z-20 flex flex-col px-6 pb-56 pt-6 md:pb-6 md:pt-40">
            <div className="mt-auto flex items-center space-x-1 text-xs font-medium">
              Amet mollit aliquip
              <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
            </div>
            <p className="mt-2 text-xs text-muted-foreground">
              Elit non et commodo do reprehenderit ad excepteur mollit.
            </p>
          </div>
          <div className="absolute inset-0 top-[32%] md:top-0">
            <img
              src="https://www.shadcnblocks.com/images/block/placeholder-2.svg"
              alt="placeholder"
              className="object-fit size-full object-right-top md:h-2/3 md:object-top"
            />
          </div>
        </div>
      </NavigationMenuLink>
    </div>
    <div className="grid gap-4 md:col-span-1">
      <NavigationMenuLink
        href="#"
        className="group flex w-full items-center rounded-lg border border-border lg:rounded-xl"
      >
        <div className="flex items-start p-6 text-left">
          <Users className="size-8" />
          <div className="ml-4">
            <div className="mb-1 mt-auto text-sm font-bold text-foreground/85 hover:text-foreground">
              Incididunt Labore
            </div>
            <p className="text-xs text-muted-foreground group-hover:text-foreground">
              Velit incididunt duis id consequat elit.
            </p>
          </div>
        </div>
      </NavigationMenuLink>
      <NavigationMenuLink
        href="#"
        className="group flex w-full items-center rounded-lg border border-border lg:rounded-xl"
      >
        <div className="flex items-start p-6 text-left">
          <Computer className="size-8" />
          <div className="ml-4">
            <div className="mb-1 mt-auto text-sm font-bold text-foreground/85 hover:text-foreground">
              Elit Eonsequat
            </div>
            <p className="text-xs text-muted-foreground group-hover:text-foreground">
              Consequat nulla ex culpa aliquip ad.
            </p>
          </div>
        </div>
      </NavigationMenuLink>
    </div>
  </div>
);

const ResourcesMenu = () => (
  <div className="grid gap-y-12 md:grid-cols-2 md:gap-x-6 lg:grid-cols-4 lg:gap-6">
    <div className="col-span-1">
      <NavigationMenuLink
        href="#"
        className="group relative flex h-full overflow-hidden rounded-lg bg-primary p-0 text-primary-foreground lg:rounded-xl"
      >
        <div className="relative z-10 flex w-full flex-col-reverse text-left">
          <div className="relative z-20 flex flex-col px-6 pb-56 pt-6 md:pb-6 md:pt-40">
            <div className="mt-auto flex items-center space-x-1 text-xs">
              Consectetur
              <ArrowRight className="ml-1 size-4 transition-transform group-hover:translate-x-1" />
            </div>
            <p className="mt-2 text-xs">
              Esse minim excepteur minim consequat sunt ut voluptate
            </p>
          </div>
          <div className="absolute inset-0">
            <img
              src="https://www.shadcnblocks.com/images/block/placeholder-1.svg"
              alt="placeholder"
              className="size-full object-cover object-center invert"
            />
          </div>
          <div className="absolute inset-x-0 top-0 z-10 h-3/5 bg-[linear-gradient(hsl(var(--primary))_50%,transparent)] md:bottom-[-10%] md:top-auto md:h-[50%] md:bg-[linear-gradient(transparent,hsl(var(--primary))_50%)]"></div>
        </div>
      </NavigationMenuLink>
    </div>
    <div className="lg:col-span-2 lg:flex lg:flex-col">
      <div>
        <div className="mb-4 border-border pb-3 text-left md:mb-6 lg:border-b">
          <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
            Velit veniam culpa
          </strong>
        </div>
      </div>
      <menu className="grid gap-y-4 lg:h-full lg:grid-cols-2 lg:gap-6">
        {resources.map((resource) => (
          <NavigationMenuLink
            key={resource.id}
            href={resource.href}
            className="group flex items-center space-x-4 rounded-md border-border bg-accent px-6 py-5 text-left md:space-x-5 lg:border lg:bg-background lg:p-5"
          >
            <resource.icon className="size-6 sm:size-7" />
            <div className="ml-4 flex-1">
              <div className="text-sm font-medium text-foreground/85 group-hover:text-foreground">
                {resource.title}
              </div>
              <p className="mt-1 text-xs text-muted-foreground group-hover:text-foreground">
                {resource.description}
              </p>
            </div>
            <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
          </NavigationMenuLink>
        ))}
      </menu>
    </div>
    <div className="col-span-1 md:col-span-2 lg:col-span-1">
      {topicGroups.map((group) => (
        <Fragment key={group.title}>
          <div className="mb-4 border-border pb-3 text-left md:col-span-2 md:mb-7 lg:border-b">
            <strong className="text-left text-xs font-medium uppercase tracking-wider text-muted-foreground">
              Et dolor magna veniam
            </strong>
          </div>
          <menu className="mb-7 grid md:grid-cols-2 md:gap-x-6 lg:grid-cols-1 lg:gap-x-0">
            {group.topics.map((topic) => (
              <NavigationMenuLink
                key={topic.id}
                href={topic.href}
                className="group flex items-center space-x-6 border-b border-border py-5 text-left sm:py-8 lg:space-x-4 lg:border-0 lg:py-0"
              >
                <div className="flex aspect-square size-9 shrink-0 items-center justify-center">
                  <topic.icon className="size-5" />
                </div>
                <div className="flex-1 text-xs font-medium text-foreground/85 group-hover:text-foreground md:text-sm">
                  {topic.title}
                </div>
                <ArrowRight className="size-4 transition-transform group-hover:translate-x-1 lg:hidden" />
              </NavigationMenuLink>
            ))}
          </menu>
        </Fragment>
      ))}
    </div>
  </div>
);

const Navbar = () => {
  const [open, setOpen] = useState(false);
  const [submenu, setSubmenu] = useState<
    | 'solutions'
    | 'products'
    | 'global'
    | 'customers'
    | 'partners'
    | 'resources'
    | null
  >(null);
  return (
    <section className="fixed inset-x-0 top-0 z-20 bg-background w-full flex justify-center">
      <div className="container">
        <NavigationMenu className="min-w-full">
          <div className="flex w-full justify-between gap-2 py-4">
            <div className="flex items-center gap-2 xl:gap-8">
              <a href="#">
                <img
                  src="https://www.shadcnblocks.com/images/block/logos/astro.svg"
                  alt="Logo"
                  className="h-auto w-[80px]"
                />
              </a>
              <NavigationMenuList className="hidden lg:flex">
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Solutions
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <SolutionsMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Products
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <ProductsMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Global Guidance
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <GlobalGuidanceMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Customers
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <CustomersMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Partners
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <PartnersMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
                <NavigationMenuItem>
                  <NavigationMenuTrigger className="text-xs xl:text-sm">
                    Resources
                  </NavigationMenuTrigger>
                  <NavigationMenuContent className="min-w-[calc(100vw-4rem)] p-12 2xl:min-w-[calc(1400px-4rem)]">
                    <ResourcesMenu />
                  </NavigationMenuContent>
                </NavigationMenuItem>
              </NavigationMenuList>
            </div>
            {/* NAVBAR - RIGHT */}
            <div id='navbar-right' className="flex items-center gap-2">
              <Button variant="link" className="text-xs sm:text-sm md:hidden">
                Discover the campus life
              </Button>
              <Button className="hidden md:block">Discover the campus life</Button>
              <Button
                variant="ghost"
                size="icon"
                aria-label="Main Menu"
                className="lg:hidden"
                onClick={() => {
                  if (open) {
                    setOpen(false);
                    setSubmenu(null);
                  } else {
                    setOpen(true);
                  }
                }}
              >
                {!open && <Menu className="size-4" />}
                {open && <X className="size-4" />}
              </Button>
              <ModeToggle />
            </div>
          </div>

          {/* Mobile Menu */}
          {open && (
            <div className="fixed inset-0 top-[72px] flex h-[calc(100vh-72px)] w-full flex-col overflow-scroll border-t border-border bg-background lg:hidden">
              {submenu && (
                <div className="mt-3 px-4">
                  <Button variant="link" onClick={() => setSubmenu(null)}>
                    <ArrowLeft className="mr-2 size-4 text-xs" />
                    Go back
                  </Button>
                </div>
              )}
              {submenu === null && (
                <div>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('solutions')}
                  >
                    <span className="flex-1 text-sm font-medium">
                      Solutions
                    </span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('products')}
                  >
                    <span className="flex-1 text-sm font-medium">Products</span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('global')}
                  >
                    <span className="flex-1 text-sm font-medium">
                      Global Guidance
                    </span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('customers')}
                  >
                    <span className="flex-1 text-sm font-medium">
                      Customers
                    </span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('partners')}
                  >
                    <span className="flex-1 text-sm font-medium">Partners</span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                  <button
                    type="button"
                    className="flex w-full items-center border-b border-border px-8 py-6 text-left"
                    onClick={() => setSubmenu('resources')}
                  >
                    <span className="flex-1 text-sm font-medium">
                      Resources
                    </span>
                    <span className="shrink-0">
                      <ArrowRight className="size-4" />
                    </span>
                  </button>
                </div>
              )}
              {submenu === 'solutions' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">Solutions</h2>
                  <SolutionsMenu />
                </div>
              )}
              {submenu === 'products' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">Products</h2>
                  <ProductsMenu />
                </div>
              )}
              {submenu === 'global' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">
                    Global Guidance
                  </h2>
                  <GlobalGuidanceMenu />
                </div>
              )}
              {submenu === 'customers' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">Customers</h2>
                  <CustomersMenu />
                </div>
              )}
              {submenu === 'partners' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">Partners</h2>
                  <PartnersMenu />
                </div>
              )}
              {submenu === 'resources' && (
                <div className="container">
                  <h2 className="pb-6 pt-4 text-lg font-medium">Resources</h2>
                  <ResourcesMenu />
                </div>
              )}
              {/* Mobile menu footer */}
              <div className="mx-8 mt-auto flex flex-col items-center gap-8 py-24">
                <Button>Request a proposal</Button>
                <div className="flex flex-col items-center gap-2">
                  <p className="text-xs">Talk to an expert:</p>
                  <a
                    href="#"
                    className="text-xs text-foreground/85 hover:text-foreground"
                  >
                    Get in touch
                  </a>
                </div>
                <p className="text-xs">Copyright &copy; All Rights Reserved.</p>
              </div>
            </div>
          )}
        </NavigationMenu>
      </div>
    </section>
  );
};

export { Navbar };
