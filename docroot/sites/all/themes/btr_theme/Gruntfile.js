module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    watch: {
      livereload: {
        options: {
          livereload: true
        },
        files: [
          'js/script.js',
          'css/**/*']
      },
      images: {
        files: ['images/**']
      },
      css: {
        files: 'sass/**/*.scss',
        tasks: ['compass:dev']
      },
      js: {
        files: [
          'js/{,**/}*.js',
          '!js/{,**/}*.min.js',
          '!js/script.js'],
        tasks: ['jshint', 'concat', 'uglify:dist']
      }
    },

    compass: {
      options: {
        config: 'config.rb',
        bundleExec: true,
        force: true
      },
      dev: {
        options: {
          environment: 'development'
        }
      },
      dist: {
        options: {
          environment: 'production'
        }
      }
    },

    jshint: {
      options: {
        jshintrc: '.jshintrc'
      },
      all: ['js/source/custom/**/*.js']
    },

    concat: {
      dist: {
        src: [
          // Bootrap JS; Must be loaded in a particular order
          // @see https://github.com/twbs/bootstrap-sass/blob/master/js/bootstrap-sprockets.js
          'js/source/contrib/bootstrap/affix.js',
          //'js/source/contrib/bootstrap/alert.js',
          'js/source/contrib/bootstrap/button.js',
          //'js/source/contrib/bootstrap/carousel.js',
          'js/source/contrib/bootstrap/collapse.js',
          'js/source/contrib/bootstrap/dropdown.js',
          'js/source/contrib/bootstrap/tab.js',
          'js/source/contrib/bootstrap/transition.js',
          //'js/source/contrib/bootstrap/scrollspy.js',
          //'js/source/contrib/bootstrap/modal.js',
          'js/source/contrib/bootstrap/tooltip.js',
          'js/source/contrib/bootstrap/popover.js',
          // JQuery Cookie
          'js/source/contrib/_jquery-cookie.js',
          // Radix
          'js/source/contrib/radix-script.js',
          // Theme specific
          'js/source/custom/**/*.js'
        ],
        dest: 'js/script.js'
      }
    },

    uglify: {
      dev: {
        options: {
          mangle: false,
          compress: false,
          beautify: true
        },
        files: [{
          expand: true,
          flatten: true,
          cwd: 'js',
          src: ['script.js'],
          dest: 'js'
        }]
      },
      dist: {
        options: {
          mangle: true,
          compress: true
        },
        files: [{
          expand: true,
          flatten: true,
          cwd: 'js',
          src: ['script.js'],
          dest: 'js'
        }]
      }
    },

    pagespeed: {
      options: {
        nokey: true,
        url: "http://loopduplicate.com"
      },
      prod: {
        options: {
          url: "http://loopduplicate.com/content/one-crazy-way-to-theme-a-fieldable-panels-pane-to-get-exactly-the-markup-you-want",
          locale: "en_GB",
          strategy: "desktop",
          threshold: 80
        }
      },
      paths: {
        options: {
          paths: ["/"],
          locale: "en_GB",
          strategy: "desktop",
          threshold: 80
        }
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-compass');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-pagespeed');

  grunt.registerTask('default', [
    'compass:dev',
    'watch'
  ]);
};