require 'models'
require 'sinatra'
require 'sanitize'

class Main < Sinatra::Base
  enable :sessions
  set :sessions, :httponly => false # even if httponly cookies are used, XSS still hijacks a session
  disable :protection # doesn't really do much for us

  set :haml, :format => :html5, :layout => :'layout.html'

  helpers do
    def profile_sanitize(profile)
      # Whitelist-based HTML sanitization
      Sanitize.clean(profile,
        :elements => [
          'a', 'abbr', 'b', 'bdo', 'blockquote', 'br', 'caption', 'cite', 'code', 'col', 'colgroup',
          'dd', 'del', 'dfn', 'div', 'dl', 'dt', 'em', 'figcaption', 'figure', 'h1', 'h2', 'h3', 'h4',
          'h5', 'h6', 'hgroup', 'i', 'img', 'ins', 'kbd', 'li', 'mark', 'ol', 'p', 'pre', 'q', 'rp',
          'rt', 'ruby', 's', 'samp', 'small', 'span', 'strike', 'strong', 'sub', 'sup', 'table', 'tbody',
          'td', 'tfoot', 'th', 'thead', 'tr', 'u', 'ul', 'var', 'wbr'
        ],
        :attributes => { :all => [
          'abbr', 'align', 'alt', 'axis', 'class', 'cite', 'colspan', 'datetime', 'dir', 'height', 'href',
          'id', 'lang', 'pubdate', 'reversed', 'rowspan', 'scope', 'span', 'src', 'start', 'summary',
          'title', 'type', 'width'
        ]}
      )
    end

    def rand_seq(len)
      return (0...len).map{ ('a'..'z').to_a[rand(26)] }.join
    end
  end

  before do
    @user = User.find_by_id(session[:user_id])
  end

  before do
    # csrf protection
    if ['POST', 'PUT'].include? request.request_method
      halt 403 unless params[:csrf] == session[:csrf]
    end
    if [ '/', '/transfer' ].include? request.path_info
      session[:csrf] = rand_seq(20)
    end
  end

  post '/login' do
    if params[:register]
      @user = User.create! :name => params[:name], :password => params[:password]
    else
      # If there is a 'guest' user, then no password is needed to login
      if params[:name] == 'guest'
        @user = User.find_by_name(params[:name])
      else
        @user = User.find_by_name_and_password(params[:name], params[:password])
      end
    end
    session[:user_id] = @user.id if @user
    session[:logo_path] = rand_seq(10) + '.png'
    redirect to('/')
  end

  get '/logout' do
    session.delete(:user_id)
    redirect to('/')
  end

  get '/' do
    if @user
      @title = "Profile"
      haml :'profile.html'
    else
      @title = "Login"
      haml :'login.html'
    end
  end

  post '/update' do
    return 403 unless @user
    @user.name = params[:name] if params[:name]
    @user.profile = params[:profile] if params[:profile]
    @user.save!
    redirect to('/')
  end

  get '/search' do
    return redirect to('/') unless @user
    @title = "Search"
    @q = params[:q]
    @search_user = User.find_by_name(@q) if @q
    haml :'search.html'
  end

  get '/transfer' do
    return redirect to('/') unless @user
    @title = "Transfer"
    haml :'transfer.html'
  end

  post '/transfer' do
    return 403 unless @user
    @attempted = true
    @result = @user.transfer_to(User.find_by_name(params[:name]), params[:amount].to_i)
    haml :'transfer.html'
  end

  # Don't want just anyone seeing our AWESOME logo!
  get '/secret/:path' do
    return 403 unless @user and params[:path] == session[:logo_path]
    send_file 'private/logo.png'
  end

  ###### FOR GRADING ONLY #####

  get '/cookie' do
    @cookie = params[:cookie]
    haml :'cookie.html', :layout => false
  end
end
