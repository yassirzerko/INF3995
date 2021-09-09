import React from "react";
import {shallow } from "enzyme";
import ConnexionStatus from "./ConnexionStatus";
import Table from "@material-ui/core/Table";

describe("Connection Status", () => {
  it("should render initial layout", () => {
    const component = shallow(<ConnexionStatus />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("should render table", () => {
    const component = shallow(<ConnexionStatus />);
    expect(component.find(Table).length).toBe(1);
  });
});
