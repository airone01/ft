$(document).ready(function () {
  // Scroll tracking
  function onScroll() {
    const scrollPosition = $(window).scrollTop();

    // Check which section is currently in view
    $('section').each(function () {
      const sectionTop = $(this).offset().top;
      const sectionHeight = $(this).outerHeight();

      if (scrollPosition >= sectionTop - 50 &&
        scrollPosition < sectionTop + sectionHeight - 50) {

        const id = $(this).attr('id');

        $('.nav-button').removeClass('active');
        $(`.nav-button[href="#${id}"]`).addClass('active');
      }
    });
  }
  $(window).scroll(onScroll);
  onScroll();

  // Smooth scrolling when clicking on navigation buttons
  $('.nav-button').click(function (e) {
    e.preventDefault();

    const targetSection = $($(this).attr('href'));

    $('html, body').animate({
      scrollTop: targetSection.offset().top
    }, 800);
  });

  const fadeElements = $('.fade-in');

  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        $(entry.target).addClass('active');
      }
    });
  }, {
    threshold: 0.1
  });

  fadeElements.each(function () {
    observer.observe(this);
  });

  // Smooth scrolling for navigation links
  $('a[href^="#"]').click(function (e) {
    e.preventDefault();

    $('html, body').animate({
      scrollTop: $($(this).attr('href')).offset().top
    }, 800);
  });

  console.log('LOADED!')
});
