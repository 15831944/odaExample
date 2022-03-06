
DemoViewer
==========

#### DemoViewer web application ####

This project was bootstrapped with [Create React App](https://github.com/facebook/create-react-app).
Demo application for working with OpenCloud server

[Example](http://cloud.opendesign.com/#/)

### Config ###
Config file placed at **public\config.json**
Example:
```json 
{
  "registration_host": "http://localhost:9000",
  "api_host": "http://localhost:8080",
  "visualizejs_url": "https://dz30xdbocvzdp.cloudfront.net/libs/visualizejs/master/Visualize.js",
  "pageSize": 16,
  "refreshFilesTimeout": 5000,
  "chunkLoadingTime": 12000
}
```

### Available Scripts

In the project directory, you can run:

#### `npm start`

Runs the app in the development mode.<br>
Open [http://localhost:3000](http://localhost:3000) to view it in the browser.

The page will reload if you make edits.<br>
You will also see any lint errors in the console.

#### `npm test`

Launches the test runner in the interactive watch mode.<br>
See the section about [running tests](https://facebook.github.io/create-react-app/docs/running-tests) for more information.

#### `npm run build`

Builds the app for production to the `build` folder.<br>
It correctly bundles React in production mode and optimizes the build for the best performance.

The build is minified and the filenames include the hashes.<br>
Your app is ready to be deployed!

See the section about [deployment](https://facebook.github.io/create-react-app/docs/deployment) for more information.


### Modules ###

DemoViewer provides a modular system for creating your own application. A modular system is needed to rewrite code as less as possible, just add new ones to their place. Or replace the old with new ones. The modular Redux system is used.

*Module file (notification.js) example:*
```javascript
export const TYPES = {
  ADD_NOTIFICATION: "ADD_NOTIFICATION",
  REMOVE_NOTIFICATION: "REMOVE_NOTIFICATION"
}

export const actions = {
  addNotification: () => {
    return (type, text) => dispatch => {
      dispatch({ type: TYPES.ADD_NOTIFICATION, payload: { type, text } });
    }
  },
  removeNotification: (id) => dispatch => {
    dispatch({ type: TYPES.REMOVE_NOTIFICATION, payload: id });
  }
}

export const reducer = (state = {
  list: [],
  nextId: 0
}, action) => {
  switch (action.type) {
    case TYPES.ADD_NOTIFICATION:
      return { ...state, list: state.list.concat({ ...action.payload, id: state.nextId }), nextId: ++state.nextId };
    case TYPES.REMOVE_NOTIFICATION:
      return { ...state, list: state.list.filter(item => item.id !== action.payload) }
    default: return state;
  }
}

```

### Learn More
--------------

You can learn more in the [Create React App documentation](https://facebook.github.io/create-react-app/docs/getting-started).

To learn React, check out the [React documentation](https://reactjs.org/).

#### Making a Progressive Web App

This section has moved here: https://facebook.github.io/create-react-app/docs/making-a-progressive-web-app

#### Deployment

This section has moved here: https://facebook.github.io/create-react-app/docs/deployment

#### `npm run build` fails to minify

This section has moved here: https://facebook.github.io/create-react-app/docs/troubleshooting#npm-run-build-fails-to-minify

#### Learn Redux

This section has moved here: https://redux.js.org/basics/basic-tutorial