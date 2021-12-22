Rails.application.routes.draw do
  get 'courses/:id' => 'courses#show'
  get 'courses' => 'courses#showall'
  get 'faculties/:id' => 'faculties#show'
  resources :students
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
